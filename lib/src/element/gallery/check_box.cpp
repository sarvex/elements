/*=============================================================================
   Copyright (c) 2016-2020 Joel de Guzman

   Distributed under the MIT License [ https://opensource.org/licenses/MIT ]
=============================================================================*/
#include <elements/element/gallery/check_box.hpp>

namespace cycfi { namespace elements
{
   void check_box_element::draw(context const& ctx)
   {
      auto&       canvas_ = ctx.canvas;
      auto        canvas_state = canvas_.new_state();
      auto const& theme_ = get_theme();
      color const indicator_color = theme_.indicator_color;
      rect        box = ctx.bounds.move(15, 0);

      box.width(box.height());
      bool        state = value() > 1;
      bool        hilite = value() & 1;

      color c1 = state ?
         (hilite? theme_.indicator_hilite_color : theme_.indicator_bright_color) :
         colors::black.opacity(theme_.element_background_opacity)
         ;

      if (state)
         draw_icon(canvas_, box, icons::ok, 14, c1);

      color outline_color = hilite? theme_.frame_hilite_color : theme_.frame_color;
      canvas_.begin_path();
      canvas_.round_rect(box.inset(1, 1), 3);
      canvas_.stroke_style(outline_color);
      canvas_.stroke();

      // Pseudo glow
      canvas_.round_rect(box, 4);
      canvas_.stroke_style(outline_color.opacity(0.1));
      canvas_.stroke();

      canvas_.fill_style(theme_.label_font_color);
      canvas_.font(
         theme_.label_font,
         theme_.label_font_size
      );
      canvas_.text_align(canvas_.left | canvas_.middle);
      float cx = box.right + 10;
      float cy = ctx.bounds.top + (ctx.bounds.height() / 2);
      canvas_.fill_text(point{ cx, cy }, _text.c_str());
   }
}}
