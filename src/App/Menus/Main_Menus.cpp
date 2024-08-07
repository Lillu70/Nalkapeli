
#pragma once


static void Do_Settings_Menu_Frame()
{
    void(*banner_func)(GUI_Context* context) = [](GUI_Context* context)
    {
        v2f title_scale = v2f{4.f, 4.f};
        Font* font = &context->theme->font;
        v2f back_button_dim = GUI_Tight_Fit_Text("<", font, title_scale);
        if(GUI_Do_Button(context, &GUI_AUTO_TOP_LEFT, &back_button_dim, "<"))
        {
            s_global_data.active_menu = Menus::main_menu;
        }
        
        context->layout.build_direction = GUI_Build_Direction::right_center;
        
        GUI_Do_Title_Text(context, AUTO, "Asetukset", title_scale);
        
    }; // ----------------------------------------------------------------------------------------

    void(*menu_func)(GUI_Context* context) = [](GUI_Context* context)
    {
        
    }; // ----------------------------------------------------------------------------------------

    Do_GUI_Frame_With_Banner(banner_func, menu_func, 100);
}


static void Do_Default_Quit_Popup(GUI_Context* context)
{
    GUI_Do_Title_Text(context, &GUI_AUTO_MIDDLE, "Suljetaanko varmasti?");
    
    context->layout.build_direction = GUI_Build_Direction::down_center;
    
    static constexpr char* t1 = "Peruuta ja jatka";
    static constexpr char* t2 = "Sulje";
    
    v2f button_dim = GUI_Tight_Fit_Text(t1, &s_theme.font) + s_theme.padding;
    
    if(GUI_Do_Button(context, AUTO, &button_dim, t1))
        Close_Popup();
    
    
    if(GUI_Do_Button(context, AUTO, &button_dim, t2))
        s_platform.Set_Flag(App_Flags::is_running, false);
}


static void Do_Main_Menu_Name_New_Campaign_Popup(GUI_Context* context)
{
    GUI_Do_Title_Text(context, &GUI_AUTO_MIDDLE, "Nime\xE4 uusi kampanja:");
    
    bool force_create = GUI_Do_SL_Input_Field(context, AUTO, AUTO, &s_global_data.new_campaign_name);
    
    v2f last_element_dim = context->layout.last_element.dim;
    last_element_dim.x -= context->theme->padding;
    last_element_dim.x *= 0.5f;
    
    if(GUI_Do_Button(context, AUTO, &last_element_dim, "Luo") || force_create)
    {
        s_global_data.active_menu = Menus::EE_all_events;
        Init_Event_Container_Takes_Name_Ownership(
            &s_editor_state.event_container, 
            &s_allocator, 
            &s_global_data.new_campaign_name);
        
        Serialize_Campaign(s_editor_state.event_container, &s_platform);
        
        Close_Popup();
    }
    
    context->layout.build_direction = GUI_Build_Direction::right_center;
    
    if(GUI_Do_Button(context, AUTO, &last_element_dim, "Peruuta"))
        Close_Popup();
}


static void Do_Main_Menu_Frame()
{
    Assert(s_mem.push_call_count == s_mem.free_call_count);
    
    Clear_Canvas(&s_canvas, s_background_color);
    
    v2f def_text_scale = GUI_DEFAULT_TEXT_SCALE;
    
    GUI_DEFAULT_TEXT_SCALE = v2f{3, 3};
    
    GUI_Context* context = &s_gui_banner;
    GUI_Begin_Context(
        context,
        &s_canvas, 
        &s_global_data.action_context, 
        &s_theme,
        v2i{0, 0},
        GUI_Anchor::top);
    
    v2f title_scale = v2f{7.f, 7.f};
    GUI_Do_Title_Text(context, &GUI_AUTO_TOP_CENTER, "Tarina Kuolemaan", title_scale);
    
    
    GUI_Do_Spacing(context, AUTO);
    
    context->layout.build_direction = GUI_Build_Direction::down_center;
    
    static constexpr char* button_texts[] = 
    {
        "Jatka",
        "Uusi Peli",
        "Lataa Peli",
        "Avaa editori",
        "Asetukset",
        "Sulje"
    };

    v2f dim = GUI_Tight_Fit_Multi_Line_Text(
        &context->theme->font, 
        (char**)button_texts, 
        Array_Lenght(button_texts));
    dim += context->theme->padding;
    
    
    u32 i = 0;
    // Continue
    if(GUI_Do_Button(context, AUTO, &dim, button_texts[i++]))
    {
        
    }
    
    // New game
    if(GUI_Do_Button(context, AUTO, AUTO, button_texts[i++]))
    {
        Gather_Editor_Format_Campaigns();
        s_global_data.active_menu = Menus::select_campaign_to_play_menu;
    }
    
    // Load game
    if(GUI_Do_Button(context, AUTO, AUTO, button_texts[i++]))
    {
        
    }
    
    // Open editor
    if(GUI_Do_Button(context, AUTO, AUTO, button_texts[i++]))
    {
        Gather_Editor_Format_Campaigns();
        s_global_data.active_menu = Menus::campaigns_menu;
    }
    
    // Settings
    if(GUI_Do_Button(context, AUTO, AUTO, button_texts[i++]))
    {
        s_global_data.active_menu = Menus::settings_menu;
    }
    
    // Close 
    if(GUI_Do_Button(context, AUTO, AUTO, button_texts[i++]))
    {
        s_global_data.force_quit_popup = true;
    }
    
    GUI_End_Context(context);
    
    GUI_DEFAULT_TEXT_SCALE = def_text_scale;
}