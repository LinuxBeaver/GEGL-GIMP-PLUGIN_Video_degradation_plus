/* This file is an image processing operation for GEGL
 *
 * GEGL is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * GEGL is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with GEGL; if not, see <https://www.gnu.org/licenses/>.
 *
 * Credit to Øyvind Kolås (pippin) for major GEGL contributions

 * Exchange one color with the other (settable threshold to convert from
 * one color-shade to another...might do wonders on certain images, or be
 * totally useless on others).
 *
 * Author: Adam D. Moss <adam@foxbox.org>
 *
 * GEGL port: Thomas Manni <thomas.manni@free.fr>
 *
 * 2023, Beaver's fork that allows Video Degradation to blend with all of Gimp's blend modes.
 * in default gegl:video-degradation works as if it blended with the "Overlay" blend mode
 * and users are not free to change blend modes. Beaver's fork allows users to choose their blend
 * mode using Gimp's blend modes.

If you give this information to Gimp's GEGL Graph you can recreate the plugin without installing i.t 

id=1 src  aux=[ ref=1 color value=#808080 ] crop
video-degradation
hue-chroma chroma=0 
lens-distortion zoom=0

 */


#include "config.h"
#include <glib/gi18n-lib.h>

#ifdef GEGL_PROPERTIES

enum_start (gegl_video_degradation_fork_type)
  enum_value (GEGL_VIDEO_DEGRADATION_TYPE_STAGGERED, "staggered",
              N_("Staggered"))
  enum_value (GEGL_VIDEO_DEGRADATION_TYPE_LARGE_STAGGERED, "large-staggered",
              N_("Large staggered"))
  enum_value (GEGL_VIDEO_DEGRADATION_TYPE_STRIPED, "striped",
              N_("Striped"))
  enum_value (GEGL_VIDEO_DEGRADATION_TYPE_WIDE_STRIPED, "wide-striped",
              N_("Wide striped"))
  enum_value (GEGL_VIDEO_DEGRADATION_TYPE_LONG_STAGGERED, "long-staggered",
              N_("Long staggered"))
  enum_value (GEGL_VIDEO_DEGRADATION_TYPE_3X3, "3x3",
              N_("3x3"))
  enum_value (GEGL_VIDEO_DEGRADATION_TYPE_LARGE_3X3, "large-3x3",
              N_("Large 3x3"))
  enum_value (GEGL_VIDEO_DEGRADATION_TYPE_Hex, "hex",
              N_("Hex"))
  enum_value (GEGL_VIDEO_DEGRADATION_TYPE_DOTS, "dots",
              N_("Dots"))
enum_end (GeglVideoDegradationForkType)

property_enum (pattern, _("Pattern"), GeglVideoDegradationForkType,
               gegl_video_degradation_fork_type,
               GEGL_VIDEO_DEGRADATION_TYPE_STRIPED)
  description (_("Type of RGB pattern to use"))

property_boolean (additive, _("Additive"), TRUE)
  description(_("Whether the function adds the result to the original image."))

property_boolean (rotated, _("Rotated"), FALSE)
  description(_("Whether to rotate the RGB pattern by ninety degrees."))


#define APPLY_VIDEO_DEGRADATION_ON_THIS \
" id=1 src  aux=[ ref=1 color value=#808080 ] id=2 crop aux=[ ref=2 ] "\


property_double (chroma, _("Chroma Color Enhancer"), 0.0)
   description  (_("Chroma adjustment"))
   value_range  (-50.0, 50.0)

property_double (zoom, _("Size Increasement"), 0.0)
   description  (_("Size Increasement of the degradation effect."))
   value_range  (0.00, 100.0)

#else

#define GEGL_OP_META
#define GEGL_OP_NAME     video_degradation_mod
#define GEGL_OP_C_SOURCE video-degradation-mod.c

#include "gegl-op.h"

static void attach (GeglOperation *operation)
{
  GeglNode *gegl = operation->node;
  GeglNode *input, *output, *chroma, *zoom, *graph, *video;

  input    = gegl_node_get_input_proxy (gegl, "input");
  output   = gegl_node_get_output_proxy (gegl, "output");


  video = gegl_node_new_child (gegl,
                                  "operation", "gegl:video-degradation",
                                  NULL);

  chroma = gegl_node_new_child (gegl,
                                  "operation", "gegl:hue-chroma",
                                  NULL);

  zoom = gegl_node_new_child (gegl,
                                  "operation", "gegl:lens-distortion",
                                  NULL);


  graph = gegl_node_new_child (gegl,
                                  "operation", "gegl:gegl", "string", APPLY_VIDEO_DEGRADATION_ON_THIS,
                                  NULL);

 gegl_operation_meta_redirect (operation, "additive", video, "additive");
 gegl_operation_meta_redirect (operation, "rotated", video, "rotated");
 gegl_operation_meta_redirect (operation, "pattern", video, "pattern");
 gegl_operation_meta_redirect (operation, "zoom", zoom, "zoom");
 gegl_operation_meta_redirect (operation, "chroma", chroma, "chroma");

  gegl_node_link_many (input, graph, video, chroma, zoom, output, NULL);

}

static void
gegl_op_class_init (GeglOpClass *klass)
{
  GeglOperationClass *operation_class;

  operation_class = GEGL_OPERATION_CLASS (klass);

  operation_class->attach = attach;

  gegl_operation_class_set_keys (operation_class,
    "name",        "lb:video-degradation-mod",
    "title",       _("Video Degradation mod"),
    "reference-hash", "mod456j6bfghd50f435sf27ac",
    "description", _("Add scan lines and dots reminiscent of an old video monitor. This filter is a fork of GEGL's existing video-degradation filter. Please blend this with Gimp blend modes. (Fusing with Overlay resembles default) but Grain Extract and others create interesting effects."
                     ""),
    NULL);
}

#endif

