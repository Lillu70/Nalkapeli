
#pragma once

static f32 s_player_creation_collumn_min_width = 300;
static f32 s_player_creation_text_box_width = s_player_creation_collumn_min_width - 50;
static v2f s_player_picture_dim 
    = v2f{s_player_creation_text_box_width, s_player_creation_text_box_width};


static void Do_Load_Failed_Popup(GUI_Context* context);
static void Free_Invalid_Event_Filter_Result_Memory();
static void Do_Display_Invalid_Event_Filter_Results_Popup(GUI_Context* context);


static void Do_Create_Player_FI_Instruction_Popup(GUI_Context* context)
{
    static String instruction_text = {};
    if(!instruction_text.buffer)
    {
        Init_String(&instruction_text, &s_allocator, 
        "Here is another video inspired by the Deus Ex series!\n"
        "I hope you all enjoy it.\n"
        "I love making music like this that has more tense rhythmic elements,\n"
        "as it\'s closer to a lot of the music I compose for my full time work.\n"
        "This track feels like the music,\n"
        "that plays when you are stealthily sneaking around hostile territory,\n"
        "possibly to hack into a system or quietly take down a target.\n" 
        "I hope it helps you feel energized and productive!\n"
        "Please help my channel by sharing, liking, commenting and subscribing!\n"
        "\n\nSee you in the next one");
    }
    
    v2f title_scale = GUI_DEFAULT_TEXT_SCALE * 1.5f;
    
    static constexpr char* title_text = "Pelihahmon luonti ohjeet";
    v2f d = GUI_Tight_Fit_Text(title_text, &context->theme->font, title_scale);
    v2f b = v2f{d.y, d.y};
    
    context->layout.anchor = GUI_Anchor::center;
    
    v2f dim = v2f{d.x + context->theme->padding + b.x, 400.f};
    GUI_Do_ML_Input_Field(
        context, 
        &GUI_AUTO_MIDDLE, 
        &dim, 
        &instruction_text,
        GUI_NO_CHARACTER_LIMIT,
        GUI_DEFAULT_TEXT_SCALE,
        GUI_Character_Check_View_Only);
    
    context->layout.build_direction = GUI_Build_Direction::up_left;
    GUI_Do_Title_Text(context, AUTO, title_text, title_scale);
    
    context->layout.build_direction = GUI_Build_Direction::right_center;
    if(GUI_Do_Button(context, AUTO, &b, "X"))
        Close_Popup();
    
    // TODO: Check if this line is neccecary!
    context->layout.build_direction = GUI_Build_Direction::down_center;
    
}


static void Do_Out_Of_Template_Names_Popup(GUI_Context* context)
{
    v2f title_scale = GUI_DEFAULT_TEXT_SCALE * 1.5f;
    
    GUI_Do_Title_Text(
        context, 
        &GUI_AUTO_MIDDLE, 
        "Hupsis, valmiit nimet loppuivat kesken.", 
        title_scale);
    
    context->layout.build_direction = GUI_Build_Direction::down_center;
    
    if(GUI_Do_Button(context, AUTO, &GUI_AUTO_FIT, "Okei :("))
        Close_Popup();
}


static void Do_New_Game_Players()
{
    void(*banner_func)(GUI_Context* context) = [](GUI_Context* context)
    {
        v2f title_scale = v2f{4.f, 4.f};
        Font* font = &context->theme->font;
        v2f back_button_dim = GUI_Tight_Fit_Text("<", font, title_scale);
        if(GUI_Do_Button(context, &GUI_AUTO_TOP_LEFT, &back_button_dim, "<"))
        {
            if(s_game_state.memory)
                Delete_Game(&s_game_state, &s_allocator);
            
            s_global_data.active_menu = Menus::select_campaign_to_play_menu;
            return;
        }
        
        GUI_Push_Layout(context);
        
        context->layout.build_direction = GUI_Build_Direction::right_center;
        
        GUI_Do_Title_Text(context, AUTO, "Kampanjan pelaajat", title_scale);
        
        f32 title_height = context->layout.last_element.dim.y;
        f32 title_max_x = context->layout.last_element.rect.max.x - context->anchor_base.x;
        
        GUI_Pop_Layout(context);
        
        GUI_Do_Spacing(context, v2f{0, s_post_title_y_spacing});
        
        if(GUI_Do_Button(context, AUTO, &GUI_AUTO_FIT, "Lis\xE4\xE4 pelaaja"))
        {
            Create_Player_Name_FI(&s_game_state, &s_allocator);
            *Push(&s_game_state.player_images, &s_allocator) = {};
            
            s_gui.flags |= GUI_Context_Flags::maxout_horizontal_slider;
        }
        
        context->layout.build_direction = GUI_Build_Direction::right_center;
        
        
        if(GUI_Do_Button(context, AUTO, &GUI_AUTO_FIT, "Ohje"))
        {
            Set_Popup_Function(Do_Create_Player_FI_Instruction_Popup);
        }
        
        if(s_game_state.player_images->count)
        {
            if(GUI_Do_Button(context, AUTO, &GUI_AUTO_FIT, "T\xE4yt\xE4 tyhj\xE4t paikat"))
            {
                s_game_state.rm.seed = (i32)s_platform.Get_Time_Stamp();
                
                if(!Fill_Empty_Names(&s_game_state, &s_allocator))
                {
                    Set_Popup_Function(Do_Out_Of_Template_Names_Popup);
                }
            }            
        }
        
        GUI_Do_Text(context, AUTO, "Siemennys:", GUI_Highlight_Next(context));
        context->flags |= GUI_Context_Flags::one_time_skip_padding;
        
        f32 width = 100;
        GUI_Do_SL_Input_Field(
            context, 
            AUTO, 
            &width, 
            &s_game_state.seed_input, 
            11, 
            GUI_DEFAULT_TEXT_SCALE,
            GUI_Character_Check_Numbers_Only);
        
        // -- title bar buttons --    
        f32 padding = context->theme->padding;
        
        static constexpr char* start_game_text = "Valmista";
        
        f32 w1 = GUI_Tight_Fit_Text(start_game_text, font).x + padding;
        
        f32 buttons_width = w1 + context->dynamic_slider_girth + padding * 3;
        v2f title_row_pos = Get_Title_Bar_Row_Placement(context, title_max_x, padding, buttons_width);
        
        v2f dim = v2f{w1, title_height};
        
        b32 live_player_count = s_game_state.player_names->count; 
        if(live_player_count > 1 && GUI_Do_Button(context, &title_row_pos, &dim, start_game_text))
            s_global_data.active_menu = Menus::GM_let_the_games_begin;
        
    }; // ----------------------------------------------------------------------------------------

    void(*menu_func)(GUI_Context* context) = [](GUI_Context* context)
    {
        if(!s_game_state.memory)
            return;
        
        Dynamic_Array<Game_Player_Name_FI>* names = s_game_state.player_names;
        Player_Image* player_images = Begin(s_game_state.player_images);
        
        v2f* pos = &GUI_AUTO_TOP_LEFT;
        
        
        context->layout.build_direction = GUI_Build_Direction::right_top;
        
        u32 i = 0;
        for(auto n = Begin(names); n < End(names); ++n, ++i)
        {
            Assert(i < s_game_state.player_images->count);
            Player_Image* player_image = player_images + i; 
            Image* img = &(player_image)->image;
            
            GUI_Placement rcp = context->layout.last_element;
            
            if(GUI_Do_Button(context, pos, &GUI_AUTO_FIT, "X"))
            {
                Assert(names->count == s_game_state.player_images->count);
                
                Hollow_Player_Name_FI(n);
                Remove_Element_From_Packed_Array(Begin(names), &names->count, sizeof(*n), i);
                
                if(img->buffer)
                    s_allocator.free(img->buffer);
                
                u32* img_count = &s_game_state.player_images->count;
                Remove_Element_From_Packed_Array(player_images, img_count, sizeof(*player_images), i);
                
                if(!i)
                    pos = &GUI_AUTO_TOP_LEFT;
                
                context->layout.last_element = rcp;
                
                n -= 1;
                i -= 1;
                continue;
            }
            
            pos = 0;
            
            f32 collumn_start = GUI_Get_Collumn_Start(context, X_AXIS);
            
            GUI_Push_Layout(context);
            context->layout.build_direction = GUI_Build_Direction::right_center;
            
            GUI_Do_Text(context, AUTO, "Pelaaja");
            
            GUI_Pop_Layout(context);
            
            GUI_Push_Layout(context);
            context->layout.build_direction = GUI_Build_Direction::down_left;
            
            GUI_Do_Text(context, AUTO, "Nimi:", GUI_Highlight_Next(context));
            if(GUI_Do_SL_Input_Field(context, AUTO, &s_player_creation_text_box_width, &n->full_name))
            {
                context->selected_index += 1;
                if(!n->variant_name_1.lenght)
                {
                    Reserve_String_Memory(&n->variant_name_1, n->full_name.lenght + 1, false);
                    Mem_Copy(n->variant_name_1.buffer, n->full_name.buffer, n->full_name.lenght + 1);
                    n->variant_name_1.lenght = n->full_name.lenght;
                }
                
                if(!n->variant_name_2.lenght)
                {
                    Reserve_String_Memory(&n->variant_name_2, n->full_name.lenght + 1, false);
                    Mem_Copy(n->variant_name_2.buffer, n->full_name.buffer, n->full_name.lenght + 1);
                    n->variant_name_2.lenght = n->full_name.lenght;
                }
            }
            
            GUI_Do_Text(context, AUTO, "Muoto 1:", GUI_Highlight_Next(context));
            
            if(GUI_Do_SL_Input_Field(
                context, 
                AUTO, 
                &s_player_creation_text_box_width, 
                &n->variant_name_1))
            {
                context->selected_index += 1;
            }
            
            GUI_Do_Text(context, AUTO, "Muoto 2:", GUI_Highlight_Next(context));
            
            GUI_Do_SL_Input_Field(
                context, 
                AUTO, 
                &s_player_creation_text_box_width, 
                &n->variant_name_2);
            
            
            v2f checkbox_dim = v2f{1.f, 1.f} * context->layout.last_element.dim.y;
            GUI_Do_Checkbox(context, AUTO, &checkbox_dim, &n->special_char_override);
            
            GUI_Push_Layout(context);
            
            context->layout.build_direction = GUI_Build_Direction::right_center;
            
            GUI_Do_Text(context, AUTO, "\xC4\xE4kk\xF6s ohitus", GUI_Highlight_Prev(context));
            
            GUI_Pop_Layout(context);
            
            v2f test_button_dim = 
                v2f{s_player_creation_text_box_width, context->layout.last_element.dim.y};
            if(GUI_Do_Button(context, AUTO, &test_button_dim, "Testaa muodot"))
            {
                
            }
            
            if(GUI_Do_Button(context, AUTO, &GUI_AUTO_FIT, "Valitse kuva"))
            {
                char path[260];
                
                if(s_platform.Open_Select_File_Dialog(path, Array_Lenght(path)))
                {
                    Image loaded_img;
                    if(Load_Image_Raw(&loaded_img, path, &s_platform))
                    {
                        if(img->buffer)
                        {
                            Assert(player_image->file_path.buffer);
                            
                            player_image->file_path.free();
                            s_allocator.free(img->buffer);
                        }
                        
                        #if 1
                            img->dim = s_player_picture_dim.As<i32>();
                            u32 sm_size = img->dim.x * img->dim.y * sizeof(Color);
                            
                            img->buffer = (u8*)s_allocator.push(sm_size);
                        
                            Resize_Image(img, &loaded_img);
                            s_allocator.free(loaded_img.buffer);
                        #else
                        
                            *img = loaded_img;
                        
                        #endif
                        
                        Convert_From_RGB_To_Color_And_Flip_Y(img);
                        
                        Init_String(&player_image->file_path, &s_allocator, path);
                    }
                }
            }
            
            GUI_Push_Layout(context);
            
            context->layout.build_direction = GUI_Build_Direction::right_center;
            if(img->buffer && GUI_Do_Button(context, AUTO, &GUI_AUTO_FIT, "X"))
            {
                Assert(player_image->file_path.buffer);
                
                s_allocator.free(img->buffer);
                player_image->file_path.free();
                img->buffer = 0;
            }
            
            GUI_Pop_Layout(context);
            
            GUI_Do_Image_Panel(context, AUTO, &s_player_picture_dim, img);
            
            GUI_Pop_Layout(context);
            
            GUI_End_Collumn(
                context, 
                s_player_creation_collumn_min_width, 
                collumn_start, 
                X_AXIS);
        }
        
    }; // ----------------------------------------------------------------------------------------

    Do_GUI_Frame_With_Banner(banner_func, menu_func, 160);
}


static void Do_Let_The_Games_Begin_Frame()
{
    void(*banner_func)(GUI_Context* context) = [](GUI_Context* context)
    {
        v2f title_scale = v2f{4.f, 4.f};
        
        context->layout.anchor = GUI_Anchor::top;
        context->layout.build_direction = GUI_Build_Direction::down_center;
        
        GUI_Do_Title_Text(context, &GUI_AUTO_TOP_CENTER, s_game_state.campaign_name, title_scale);
    
        GUI_Do_Text(context, AUTO, "Osallistujat kamppailevat kuolemaan asti.");
        GUI_Do_Text(context, AUTO, "On vain yksi voittaja.");
        
        if(GUI_Do_Button(context, AUTO, &GUI_AUTO_FIT, "Aloita peli!"))
        {
            s_global_data.active_menu = Menus::GM_day_counter;
            Begin_Game(&s_game_state, &s_platform, &s_allocator);
        }
        
        context->layout.anchor = GUI_Anchor::top_left;
        v2f back_button_dim = GUI_Tight_Fit_Text("<", &context->theme->font, title_scale);
        if(GUI_Do_Button(context, &GUI_AUTO_TOP_LEFT, &back_button_dim, "<"))
        {
            s_global_data.active_menu = Menus::GM_players;
        }
        
    }; // ----------------------------------------------------------------------------------------

    void(*menu_func)(GUI_Context* context) = [](GUI_Context* context)
    {
        context->layout.anchor = GUI_Anchor::top;
        context->layout.build_direction = GUI_Build_Direction::down_center;
        
        v2f* p = &GUI_AUTO_TOP_CENTER;
        
        Player_Image* player_images = Begin(s_game_state.player_images);
        Game_Player_Name_FI* player_names = Begin(s_game_state.player_names);
        
        for(u32 i = 0; i < s_game_state.player_images->count; ++i)
        {
            char* name = (player_names + i)->full_name.buffer;
            Image* img = &(player_images + i)->image;
            
            GUI_Do_Text(context, p, name);
            p = AUTO;
            
            GUI_Do_Image_Panel(context, AUTO, &s_player_picture_dim, img);
        }
    }; // ----------------------------------------------------------------------------------------

    Do_GUI_Frame_With_Banner(banner_func, menu_func, 210);
}


static void Do_Event_Display_Frame()
{
    Assert(s_game_state.live_player_count);
    
    static Event* active_event;
    static Event_Header* active_event_header;
    static bool skip_frame;
    
    skip_frame = false;
    
    Get_Active_Event_Ref_And_Header(
        &s_game_state, 
        s_game_state.display_event_idx, 
        &active_event, 
        &active_event_header);    
    
    void(*banner_func)(GUI_Context* context) = [](GUI_Context* context)
    {        
        v2f title_scale = v2f{4.f, 4.f};
        char* event_name = active_event_header->event_name.buffer;
        GUI_Do_Title_Text(context, &GUI_AUTO_TOP_LEFT, event_name, title_scale);
        
        if(s_game_state.display_event_idx < s_game_state.active_events->count - 1)
        {
            if(GUI_Do_Button(context, AUTO, &GUI_AUTO_FIT, "Seuraava tapahtuma"))
            {
                skip_frame = true;
                s_game_state.display_event_idx += 1;
                Generate_Display_Text(&s_game_state);
            }
        }
        else
        {
            if(GUI_Do_Button(context, AUTO, &GUI_AUTO_FIT, "Jatka"))
            {
                Resolve_Current_Event_Set(&s_game_state, &s_allocator);
                skip_frame = true;
                
                if(!s_game_state.live_player_count)
                {
                    s_global_data.active_menu = Menus::GM_everyone_is_dead;
                }
                else if(s_game_state.live_player_count == 1)
                {
                    s_global_data.active_menu = Menus::GM_we_have_a_winner;
                }
                else
                {
                    switch(s_game_state.active_event_list)
                    {
                        case Event_List::day:
                        {
                            s_global_data.active_menu = Menus::GM_night_falls;
                            f64 time = s_platform.Get_Time_Stamp();
                            s_game_state.night_falls_start_time = time;
                        }break;
                        
                        case Event_List::night:
                        {
                            s_game_state.day_counter += 1;
                            Tickdown_Marks(&s_game_state);
                            s_global_data.active_menu = Menus::GM_day_counter;
                        }break;
                    }                    
                }
                return;
            }
        }
    }; // ----------------------------------------------------------------------------------------

    void(*menu_func)(GUI_Context* context) = [](GUI_Context* context)
    {
        if(skip_frame)
            return;
        
        Assert(active_event->participant_count);
        Player_Image* player_images = Begin(s_game_state.player_images);
        
        f32 collumn_start;
        v2f* p = &GUI_AUTO_TOP_LEFT;
        for(u32 i = 0; i < active_event->participant_count; ++i)
        {
            u32 player_idx = *(active_event->player_indices + i);
            Game_Player_Name_FI* player_name 
                = Begin(s_game_state.player_names) + player_idx;
            
            GUI_Do_Text(context, p, player_name->full_name.buffer);
            if(i == 0)
            {
                p = AUTO;
                GUI_Push_Layout(context);
                collumn_start = GUI_Get_Collumn_Start(context, X_AXIS);
            }
            
            Player_Image* player_image = player_images + player_idx;
            GUI_Do_Image_Panel(context, AUTO, &s_player_picture_dim, &player_image->image);
        }
        
        GUI_Pop_Layout(context);
        GUI_End_Collumn(
            context, 
            s_player_creation_collumn_min_width, 
            collumn_start, 
            X_AXIS);
        
        Rect bounds = GUI_Get_Bounds_In_Pixel_Space(context);
        f32 h = bounds.max.y - bounds.min.y;
        
        f32 last_element_x = context->layout.last_element.dim.x;
        f32 w = context->layout.last_element.pos.x + last_element_x - context->anchor_base.x;
        f32 text_box_width = f32(context->canvas->dim.x) - w - f32(context->theme->padding) * 2 - 50;
        text_box_width = Max(text_box_width, 500.f);
        
        v2f text_box_dim = v2f{text_box_width, h};
    
    
        context->layout.build_direction = GUI_Build_Direction::right_top;
        
        GUI_Do_ML_Input_Field(
            context, 
            AUTO, 
            &text_box_dim,
            &s_game_state.display_text, 
            0, 
            GUI_DEFAULT_TEXT_SCALE,
            GUI_Character_Check_View_Only);
    }; // ----------------------------------------------------------------------------------------

    Do_GUI_Frame_With_Banner(banner_func, menu_func, 200);
}


static void Do_Day_Counter_Display_Frame()
{
    static bool skip_frame;
    skip_frame = false;
    
    void(*banner_func)(GUI_Context* context) = [](GUI_Context* context)
    {
        context->layout.anchor = GUI_Anchor::top;
        context->layout.build_direction = GUI_Build_Direction::down_center;
        
        v2f title_scale = v2f{4.f, 4.f};
        GUI_Do_Title_Text(context, &GUI_AUTO_TOP_CENTER, "P\xE4iv\xE4", title_scale);
        v2f title_dim = context->layout.last_element.dim;
        
        char index_text_buffer[12] = {0};
        char* num = U32_To_Char_Buffer((u8*)&index_text_buffer, s_game_state.day_counter);
        GUI_Do_Text(context, AUTO, num, {}, title_scale);
        
        if(GUI_Do_Button(context, AUTO, &title_dim, "Jatka"))
        {
            s_global_data.active_menu = Menus::GM_event_display;
            Assign_Events_To_Participants(&s_game_state, Event_List::day, &s_allocator);
        }
        
        context->layout.anchor = GUI_Anchor::top_left;
        if(GUI_Do_Button(context, &GUI_AUTO_TOP_LEFT, &GUI_AUTO_FIT, "Lopeta peli"))
        {
            Delete_Game(&s_game_state, &s_allocator);
            s_global_data.active_menu = Menus::main_menu;
            skip_frame = true;
            return;
        }
        
    }; // ----------------------------------------------------------------------------------------

    void(*menu_func)(GUI_Context* context) = [](GUI_Context* context)
    {
        if(skip_frame)
            return;
    
        context->layout.anchor = GUI_Anchor::top;
        context->layout.build_direction = GUI_Build_Direction::down_center;
        
        GUI_Do_Text(context, &GUI_AUTO_TOP_CENTER, "Aktiiviset yleis merkit.");
        
        char num_text_buffer[12] = {0};
        
        for(each(Mark_GM*, gmark, s_game_state.global_marks))
        {
            u32 offset = *(((u32*)s_game_state.mark_table.memory) + gmark->idx);
            char* mark_text = s_game_state.mark_data + offset;
            GUI_Do_Text(context, AUTO, mark_text);
            
            GUI_Push_Layout(context);
            
            context->layout.build_direction = GUI_Build_Direction::right_center;
            char* num = U32_To_Char_Buffer((u8*)&num_text_buffer, gmark->duration);
            GUI_Do_Text(context, AUTO, num);
            
            GUI_Pop_Layout(context);
        }
        
        v2f title_scale = v2f{3.f, 3.f};
        GUI_Do_Title_Text(
            context, 
            AUTO, 
            "J\xE4ljell\xE4 olevat osallistujat.", 
            title_scale);
        
        f32 padding = f32(context->theme->padding);
        
        f32 dx = 
            (s_player_picture_dim.x * s_game_state.live_player_count) + 
            (padding * (s_game_state.live_player_count - 1));
        
        v2f p = context->layout.last_element.pos - context->anchor_base;
        p.y -= (context->layout.last_element.dim.y / 2) + (padding * 3) + GUI_DEFAULT_TEXT_SCALE.y;
        p.x -= dx / 2;
        
        Player_Image* images = Begin(s_game_state.player_images);
        Game_Player_Name_FI* names = Begin(s_game_state.player_names);

        context->layout.anchor = GUI_Anchor::top_left;
        context->layout.build_direction = GUI_Build_Direction::down_left;
        
        for(u32 i = 0; i < s_game_state.live_player_count; ++i)
        {
            Game_Player* player = s_game_state.players + i;
            
            GUI_Do_Text(context, &p, (names + i)->full_name.buffer);
            p.x += s_player_picture_dim.x + padding;
            
            GUI_Do_Image_Panel(context, AUTO, &s_player_picture_dim, &((images + i)->image));
            
            for(u32 s = 0; s < u32(Character_Stats::COUNT); ++s)
            {
                GUI_Do_Text(context, AUTO, (char*)s_stat_names[s]);
                GUI_Push_Layout(context);
                
                context->layout.build_direction = GUI_Build_Direction::right_center;
                
                context->flags |= GUI_Context_Flags::one_time_skip_padding;
                GUI_Do_Text(context, AUTO, ": ");
                context->flags |= GUI_Context_Flags::one_time_skip_padding;
                
                char* num = U32_To_Char_Buffer((u8*)&num_text_buffer, player->stats[s]);
                GUI_Do_Text(context, AUTO, num);
                
                GUI_Pop_Layout(context);
            }
            
            
            GUI_Do_Text(context, AUTO, "Esineet:");
            for(each(Mark_GM*, mark, player->marks))
            {
                if(mark->type == Mark_Type::item)
                {
                    u32 offset = *(((u32*)s_game_state.mark_table.memory) + mark->idx);
                    char* mark_text = s_game_state.mark_data + offset;
                    GUI_Do_Text(context, AUTO, mark_text);
                    
                    GUI_Push_Layout(context);
                    
                    context->layout.build_direction = GUI_Build_Direction::right_center;
                    
                    context->flags |= GUI_Context_Flags::one_time_skip_padding;
                    GUI_Do_Text(context, AUTO, ": ");
                    context->flags |= GUI_Context_Flags::one_time_skip_padding;
                    
                    char* num = U32_To_Char_Buffer((u8*)&num_text_buffer, mark->duration);
                    
                    GUI_Do_Text(context, AUTO, num);
                    
                    GUI_Pop_Layout(context);
                }
            }
            
            
            GUI_Do_Text(context, AUTO, "Hahmo merkit:");
            for(each(Mark_GM*, mark, player->marks))
            {
                if(mark->type == Mark_Type::personal)
                {
                    u32 offset = *(((u32*)s_game_state.mark_table.memory) + mark->idx);
                    char* mark_text = s_game_state.mark_data + offset;
                    GUI_Do_Text(context, AUTO, mark_text);
                    
                    GUI_Push_Layout(context);
                    
                    context->layout.build_direction = GUI_Build_Direction::right_center;
                    
                    context->flags |= GUI_Context_Flags::one_time_skip_padding;
                    GUI_Do_Text(context, AUTO, ": ");
                    context->flags |= GUI_Context_Flags::one_time_skip_padding;
                    
                    char* num = U32_To_Char_Buffer((u8*)&num_text_buffer, mark->duration);
                    
                    GUI_Do_Text(context, AUTO, num);
                    
                    GUI_Pop_Layout(context);
                }
            }
        }
        
    }; // ----------------------------------------------------------------------------------------

    Do_GUI_Frame_With_Banner(banner_func, menu_func, 220);
}


static void Do_Night_Falls_Frame()
{
    GUI_Context* context = &s_gui_banner;
    Inverse_Bit_Mask(&context->flags, GUI_Context_Flags::enable_dynamic_sliders);
    
    Clear_Canvas(&s_canvas, s_background_color);
    
    GUI_Begin_Context(
        context,
        &s_canvas,
        &s_global_data.action_context, 
        &s_theme,
        v2i{0, 0},
        GUI_Anchor::center,
        GUI_Build_Direction::down_center);
    
    Font* font = &context->theme->font;
    v2f text_scale = v2f{6.f, 6.f};
    
    f32 half_char_height = (font->char_height * text_scale.y) * 0.5f;
    f32 x = Get_Middle(context->canvas).x;
    f32 top = f32(context->canvas->dim.y - 1) - half_char_height;
    f32 bottom = 0.f - half_char_height;
    
    f64 time = s_platform.Get_Time_Stamp();
    f64 delta = time - s_game_state.night_falls_start_time;
    f64 t = delta / s_game_state.night_falls_time;
    t = Clamp_To_Barycentric(t);
    t = Square(t);
    f32 y = Lerp(top, bottom, f32(t));
    
    v2f text_pos = v2f{x, y};
    
    GUI_Do_Title_Text(context, &text_pos, "Y\xF6 laskeutuu...", text_scale);
    
    v2i cursor_pos = s_platform.Get_Cursor_Position();
    bool cursor_on_canvas = Is_Point_On_Canvas(context->canvas, cursor_pos);
    
    if(t >= 1.0 || 
        GUI_Context::actions[GUI_Menu_Actions::enter].Is_Released() ||
        (cursor_on_canvas && GUI_Context::actions[GUI_Menu_Actions::mouse].Is_Released()))
    {
        s_global_data.active_menu = Menus::GM_event_display;
        Assign_Events_To_Participants(&s_game_state, Event_List::night, &s_allocator);
    }
    
    GUI_End_Context(context);
    
    context->flags |= GUI_Context_Flags::enable_dynamic_sliders;
}


static void Do_All_Players_Are_Dead_Frame()
{
    Assert(s_game_state.live_player_count == 0);
    
    static bool skip_frame;
    
    skip_frame = false;
    
    void(*banner_func)(GUI_Context* context) = [](GUI_Context* context)
    {
        v2f title_scale = v2f{4.f, 4.f};
        
        context->layout.anchor = GUI_Anchor::top;
        context->layout.build_direction = GUI_Build_Direction::down_center;
        
        char* title_text = "Kaikki osallistujat makavat kuolleina...";
        GUI_Do_Title_Text(context, &GUI_AUTO_TOP_CENTER, title_text, title_scale);
    
        GUI_Do_Text(context, AUTO, "Kukaan ei selviytynyt!");
        
        if(GUI_Do_Button(context, AUTO, &GUI_AUTO_FIT, "Pelaa uudelleen"))
        {
            skip_frame = true;
            Reset_Game(&s_game_state, &s_allocator);
            s_global_data.active_menu = Menus::GM_let_the_games_begin;
        }
        
        if(GUI_Do_Button(context, AUTO, &GUI_AUTO_FIT, "Lopeta peli"))
        {
            skip_frame = true;
            Delete_Game(&s_game_state, &s_allocator);
            s_global_data.active_menu = Menus::main_menu;
        }
        
    }; // ----------------------------------------------------------------------------------------

    void(*menu_func)(GUI_Context* context) = [](GUI_Context* context)
    {
        if(skip_frame)
            return;
        
        Player_Image* images = Begin(s_game_state.player_images);
        Game_Player_Name_FI* names = Begin(s_game_state.player_names);
        
        GUI_Do_Text(context, &GUI_AUTO_TOP_CENTER, "Kuolleet:");
        
        for(u32 i = 1; i < s_game_state.total_player_count; ++i)
        {
            GUI_Do_Text(context, AUTO, (names + i)->full_name.buffer);
            GUI_Do_Image_Panel(context, AUTO, &s_player_picture_dim, &((images + i)->image));
        }
    }; // ----------------------------------------------------------------------------------------

    Do_GUI_Frame_With_Banner(banner_func, menu_func);
}


static void Do_We_Have_A_Winner_Frame()
{
    Assert(s_game_state.live_player_count == 1);
    
    static bool skip_frame;
    skip_frame = false;
    
    void(*banner_func)(GUI_Context* context) = [](GUI_Context* context)
    {
        v2f title_scale = v2f{4.f, 4.f};
        
        context->layout.anchor = GUI_Anchor::top;
        context->layout.build_direction = GUI_Build_Direction::down_center;
        
        GUI_Do_Title_Text(context, &GUI_AUTO_TOP_CENTER, "Voittaja on selvinnyt!", title_scale);
        GUI_Do_Text(context, AUTO, "H\xE4nen nimens\xE4 j\xE4\xE4k\xF6\xF6n histoarian kirjoihin.");
        
        if(GUI_Do_Button(context, AUTO, &GUI_AUTO_FIT, "Pelaa uudelleen"))
        {
            skip_frame = true;
            Reset_Game(&s_game_state, &s_allocator);
            s_global_data.active_menu = Menus::GM_let_the_games_begin;
        }
        
        if(GUI_Do_Button(context, AUTO, &GUI_AUTO_FIT, "Lopeta peli"))
        {
            skip_frame = true;
            Delete_Game(&s_game_state, &s_allocator);
            s_global_data.active_menu = Menus::main_menu;
        }
    }; // ----------------------------------------------------------------------------------------

    void(*menu_func)(GUI_Context* context) = [](GUI_Context* context)
    {
        if(skip_frame)
            return;
        
        context->layout.anchor = GUI_Anchor::top;
        context->layout.build_direction = GUI_Build_Direction::down_center;
        
        GUI_Do_Text(context, &GUI_AUTO_TOP_CENTER, "Voittaja!");
        
        Player_Image* images = Begin(s_game_state.player_images);
        Game_Player_Name_FI* names = Begin(s_game_state.player_names);
        
        GUI_Do_Text(context, AUTO, names->full_name.buffer);
        GUI_Do_Image_Panel(context, AUTO, &s_player_picture_dim, &images->image);
        
        v2f seperator_dim = v2f{f32(context->canvas->dim.x) - 50, 10};
        seperator_dim.x = Max(seperator_dim.x, s_player_picture_dim.x);
        
        GUI_Do_Panel(context, AUTO, &seperator_dim);
        
        GUI_Do_Text(context, AUTO, "Kuolleet:");
        
        for(u32 i = 1; i < s_game_state.total_player_count; ++i)
        {
            GUI_Do_Text(context, AUTO, (names + i)->full_name.buffer);
            GUI_Do_Image_Panel(context, AUTO, &s_player_picture_dim, &((images + i)->image));
        }
        
    }; // ----------------------------------------------------------------------------------------

    Do_GUI_Frame_With_Banner(banner_func, menu_func, 210);
}


static void Do_Select_Campagin_To_Play_Frame()
{
    void(*banner_func)(GUI_Context* context) = [](GUI_Context* context)
    {
        context->layout.build_direction = GUI_Build_Direction::right_center;
        
        v2f title_scale = v2f{4.f, 4.f};
        Font* font = &context->theme->font;
        v2f back_button_dim = GUI_Tight_Fit_Text("<", font, title_scale);
        if(GUI_Do_Button(context, &GUI_AUTO_TOP_LEFT, &back_button_dim, "<"))
        {
            s_global_data.active_menu = Menus::main_menu;
            Clear_Editor_Format_Campaigns();
        }
        
        GUI_Do_Text(context, AUTO, "Uusi peli", {}, title_scale, true);
        f32 title_height = context->layout.last_element.dim.y;
        f32 title_max_x = context->layout.last_element.rect.max.x - context->anchor_base.x;
    
    }; // ----------------------------------------------------------------------------------------

    void(*menu_func)(GUI_Context* context) = [](GUI_Context* context)
    {
        GUI_Do_Text(context, &GUI_AUTO_TOP_LEFT, "(l\xF6ydetty kohteesta \"", {}, v2f{1.f, 1.f});
        GUI_Push_Layout(context);
        context->layout.build_direction = GUI_Build_Direction::right_center;
        
        context->flags |= GUI_Context_Flags::one_time_skip_padding;
        GUI_Do_Text(context, AUTO, campaign_folder_wildcard_path, {}, v2f{1.f, 1.f});
        
        context->flags |= GUI_Context_Flags::one_time_skip_padding;
        GUI_Do_Text(context, AUTO, "\" jossa * on kampanjan nimi.)", {}, v2f{1.f, 1.f});
        
        GUI_Pop_Layout(context);
        GUI_Do_Text(context, AUTO, "Valitse kampanja:");
        
        Dynamic_Array<String>* on_disk_names = s_global_data.on_disk_campaign_names;
        if(on_disk_names)
        {
            for(String* save_name = Begin(on_disk_names); save_name < End(on_disk_names); ++save_name)
            {
                if(GUI_Do_Button(context, AUTO, &GUI_AUTO_FIT, save_name->buffer))
                {
                    Events_Container editor_format_campagin;
                    if(Load_Campaign(&editor_format_campagin, save_name, &s_allocator, &s_platform))
                    {
                        Dynamic_Array<Invalid_Event_Filter_Result>* filter_results = 
                            Unordered_Filter_Prolematic_Events(&editor_format_campagin, &s_allocator);
                        
                        if(filter_results)
                        {
                            Set_Popup_Function(Do_Display_Invalid_Event_Filter_Results_Popup);
                            s_global_data.on_popup_close = Free_Invalid_Event_Filter_Result_Memory;
                            
                            Assert(!s_global_data.IEFR);
                            s_global_data.IEFR = filter_results;
                        }
                        
                        Game_State game_state;
                
                        if(Convert_Editor_Campaign_Into_Game_Format(
                            &game_state,
                            &editor_format_campagin,
                            &s_platform,
                            &s_allocator))
                        {
                            if(s_game_state.memory)
                                Delete_Game(&s_game_state, &s_allocator);
                            
                            s_game_state = game_state;
                            
                            if(!s_global_data.IEFR)
                                s_global_data.active_menu = Menus::GM_players;
                        }

                        Delete_Event_Container(&editor_format_campagin, &s_allocator);
                    }
                    else
                    {
                        Set_Popup_Function(Do_Load_Failed_Popup);
                    }
                }
            }
        }
        
    }; // ----------------------------------------------------------------------------------------

    Do_GUI_Frame_With_Banner(banner_func, menu_func, 100);
}


static void Do_Load_Failed_Popup(GUI_Context* context)
{
    context->layout.anchor = GUI_Anchor::bottom;
    context->layout.build_direction = GUI_Build_Direction::down_center;
    
    GUI_Do_Title_Text(context, &GUI_AUTO_MIDDLE, "Jokin meni m\xF6nk\xE4\xE4n!");
    GUI_Do_Text(context, AUTO, "Kampanjaa ei voitu ladata.");
    
    GUI_Do_Spacing(context, v2f{0, 20});
    
    if(GUI_Do_Button(context, AUTO, &GUI_AUTO_FIT, "OK"))
    {
        Close_Popup();
    }
}


static void Free_Invalid_Event_Filter_Result_Memory()
{
    Assert(s_global_data.IEFR);
    
    Hollow_Invalid_Event_Filter_Results(s_global_data.IEFR);
    s_allocator.free(s_global_data.IEFR);
    
    s_global_data.IEFR = 0;
}


static void Do_Display_Invalid_Event_Filter_Results_Popup(GUI_Context* context)
{
    Assert(s_global_data.IEFR);
    
    context->layout.anchor = GUI_Anchor::bottom;
    context->layout.build_direction = GUI_Build_Direction::down_left;
    
    char* text = "Kamppania sis\xE4lsi viallisia tapahtumia!"; 
    GUI_Do_Title_Text(context, &GUI_AUTO_MIDDLE, text);
    
    for(each(Invalid_Event_Filter_Result*, IEFR, s_global_data.IEFR))
    {
        GUI_Do_Text(context, AUTO, IEFR->name.buffer);
    }
    
    if(GUI_Do_Button(context, AUTO, &GUI_AUTO_FIT, "OK"))
    {
        Close_Popup();
    }
}