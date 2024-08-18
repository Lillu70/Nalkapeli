
// ===================================
// Copyright (c) 2024 by Valtteri Kois
// All rights reserved.
// ===================================

#ifdef SINGLE
    #ifdef FILL_LOC_IDENTIFIER
        #define L(ID, ENG, FIN) ID##,
    #else
        #define L(ID,ENG, FI) case Loc_Identifier::##ID:                \
        {                                                               \
            switch(s_settings.language)                                 \
            {                                                           \
                case Language::english:                                 \
                {                                                       \
                    result = ENG;                                       \
                }break;                                                 \
                                                                        \
                case Language::finnish:                                 \
                {                                                       \
                    result = FI;                                        \
                }break;                                                 \
            }                                                           \
        }break;

    #endif
    

    // This is where single element texts go. -----------------------------
    
    L(menu_title, "T-TELLER", "T-TELLER")
    L(are_you_sure_close, "Are you sure you want to close?", "Suljetaanko varmasti?")
    L(cancel_and_continue, "Cancel and continue", "Peruuta ja jatka")
    L(close_app, "Close", "Sulje")
    L(settings_title, "Settings", "Asetukset")
    L(text_size, "Text_size", "Tekstin koko:")
    L(allow_non_uniform_text_scale, "Allow non uniform text scale?", "Salli ep\xE4 symmentrinen skaala?")
    L(jump_to_event, "Jump to event?", "Hypp\xE4\xE4 tapahtumaan?")
    L(create_new_day_event, "Create new day event", "Luo uusi p\xE4iv\xE4 tapahtuma")
    L(create_new_night_event, "Create new night event", "Luo uusi y\xF6 tapahtuma")
    L(save, "Save", "Tallenna")
    L(day_events, "Day events:", "P\xE4iv\xE4 tapahtumat:")
    L(night_events, "Night events:", "Y\xF6 tapahtumat:")
    L(add_new_parti, "Add new participant", "Lis\xE4\xE4 uusi osallistuja")
    L(delete_parti, "Delete participant", "Poista osallistujat")
    L(parti, "Participants", "Osallistujat")
    L(add_global_req, "Add new global requirement", "Lis\xE4\xE4 yleis vaatimus")
    L(event_text, "Event Text", "Tapahtuma Teksti")
    L(cons, "Consequences", "Seuraamukset")
    L(global_reqs, "Global consequences:", "Yleis vaatimukset:")
    L(global_mark, "Global mark", "Yleis merkki")
    L(duration_remaining, "Duration remaining:", "Kestoa j\xE4ljell\xE4:")
    L(add_req, "Add requirement", "Lis\xE4\xE4 vaatimus")
    L(impossible, "Impossible!", "Mahdoton!")
    L(always_true, "Always true!", "Aina totta!")
    L(event_day_name, "Event (day) name:", "Tapahtuman (p\xE4iv\xE4) nimi:")
    L(event_night_name, "Event (night) name:", "Tapahtuman (y\xF6) nimi:")
    L(add_global_con, "Add global consequence", "Lis\xE4\xE4 yleis seuraamus")
    L(global_cons, "Global consequences:", "Yleis seuraamukset:")
    L(duration, "Duration:", "Kesto:")
    L(add_con, "Add consequence", "Lis\xE4\xE4 seuraamus")
    L(only_one_death_con_is_allowed, "Only one death consequence is allowed!", "Vain yksi kuolema seuraamus on sallittu!")
    L(only_death_happens, "Only death consequence has an effect.", "Vain kuolema seuraamuksella on vaikutusta.")
    L(do_items_get_inherited, "Do items get inherited?:", "Periytyv\xE4tk\xF6 esineet?")
    L(who_inherits, "Who inherits items \\k:", "Kuka perii \\k:")
    L(campaing_editor, "Campaign Editor", "Kampanja Editori")
    L(create_new_campaing, "Create new campaign", "Luo uusi kampanja")
    L(found_from_loc, "(found from location \"", "(l\xF6ydetty kohteesta \"")
    L(where_wildcard_is_campaing_name, "\" where * is the campaign name.)", "\" jossa * on kampanjan nimi.)")
    L(load_save, "Load save:", "Lataa tallenus:")
    L(want_to_save, "Do you want the campaign to be saved?", "Tallenetaanko kampanja?")
    L(cancel, "Cancel", "Peruuta")
    L(save_and_continue, "Save and continue", "Tallena ja jatka")
    L(continue_without_saving, "Continue without saving", "Jatka tallentamatta")
    L(save_and_close, "Save and quit", "Tallenna ja sulje")
    L(close_without_saving, "Close without saving", "Sulje tallentamatta")
    L(want_to_delete, "Are you sure you want to delete?", "Poistetaanko varmasti?")
    L(_delete, "Delete", "Poista")
    L(error_report, "Error report:",  "Virhe raportti:")
    L(event_contains_following_problems, "Event contains following problems:", "Tapahtuma sis\xE4lt\xE4\xE4 seuraavat ongelmat:")
    L(errors, "Errors:", "Virheet:")
    L(warnings, "Warnings:", "Varoitukset:")
    L(name_in_use, "Name is already in use.", "Nimi on jo k\xE4yt\xF6ss\xE4.")
    L(ok, "Ok", "Okei")
    L(give_camaping_a_name, "Give new campaign a name:", "Nime\xE4 uusi kampanja:")
    L(new_campaing, "New campaign", "Uusi kampanja")
    L(create, "Create", "Luo")
    L(campaing_deletion_is_permanent, "The campaign is deleted permanently.", "Kampanja poistetaan lopullisesti.")
    L(rename_campaign, "Give the campaign a new name:", "Nime\xE4 kampanja uudellen:")
    L(confirm, "Confirm", "Vahvistaa")
    L(player_creation_instructions, "Instuction for player creation", "Pelihahmon luonti ohjeet")
    L(ran_out_of_premade_names, "Ups, premade names ran out.", "Hupsis, valmiit nimet loppuivat kesken.")
    L(sad_confirm, "Confim :(", "Vahvistaa :(")
    L(players, "Players", "Pelaajat")
    L(player, "Player", "Pelaaja")
    L(add_player, "Add player", "Lis\xE4\xE4 pelaaja")
    L(instuction, "Instuction", "Ohje")
    L(fill_empty_spots, "Fill empty spots", "T\xE4yt\xE4 tyhj\xE4t paikat")
    L(ready, "Ready", "Valmista")
    L(name, "Name:", "Nimi:")
    L(name_form_1, "Form 1:", "Muoto 1:")
    L(name_form_2, "Form 2:", "Muoto 2:")
    L(umlauts_override, "Umlauts override", "\xC4\xE4kk\xF6s ohitus")
    L(test_forms, "Test forms", "Testaa muodot")
    L(choose_image, "Choose image", "Valitse kuva")
    L(new_game, "New game", "Uusi peli")
    L(choose_campaign, "Choose campaign", "Valitse kampanja")
    L(partis_compete_to_death, "Participants compete to the death!", "Osallistujat kamppailevat kuolemaan asti!")
    L(there_is_only_one_winner, "There is only one winner.", "On vain yksi voittaja.")
    L(start_game, "Start game!", "Aloita peli!")
    L(next_event, "Next event", "Seuraava tapahtuma")
    L(_continue, "Continue", "Jatka")
    L(day, "Day", "P\xE4iv\xE4")
    L(quit_game, "Quit game", "Lopeta peli")
    L(active_global_marks, "Active global marks.", "Aktiiviset yleis merkit.")
    L(remaining_partis, "Remaining participants.", "J\xE4ljell\xE4 olevat osallistujat.")
    L(items, "Items:", "Esineet:")
    L(character_marks, "Character marks:", "Hahmo merkit:")
    L(night_falls, "Night falls...", "Y\xF6 laskeutuu...")
    L(all_partis_are_dead, "All participants lie dead...", "Kaikki osallistujat makavat kuolleina...")
    L(nobody_survived, "Nobody survived!", "Kukaan ei selviytynyt!")
    L(play_again, "Play again", "Pelaa uudelleen")
    L(the_dead, "The Dead:", "Kuolleet:")
    L(we_have_winner, "The winner has been declared!", "Voittaja on selvinnyt!")
    L(may_his_name_be_written_in_legends, "May the name be remembered forever.", "H\xE4nen nimens\xE4 j\xE4\xE4k\xF6\xF6n histoarian kirjoihin.")
    L(winner, "Winner!", "Voittaja!")
    L(event_error, "Event error :(", "Tapahtuma virhe :(")
    L(could_not_fit_every_parti, "It was not possible to assign events to every participant.", "Kaikia osallistujia ei saatu mahtumaan tapahtumaan.")
    L(something_failed, "There was an error!", "Jokin meni m\xF6nk\xE4\xE4n!")
    L(campaign_could_not_be_loaded, "The campaign could not be load.", "Kampanjaa ei voitu ladata.")
    L(campaign_contains_invalid_events, "The campaign contains broken events!", "Kamppania sis\xE4lt\xE4\xE4 viallisia tapahtumia!")
    L(for_game_functionality_they_have_been_removed, "For the functionality of the game they have been removed.", "Pelin toimivuuden takia ne oli poistettava.")
    L(continue_anyway, "Continue anyway", "Jatka siit\xE4 huolimatta")
    L(open_in_editor, "Open in editor", "Avaa editorissa")
    L(the_following_events_contain_errors, "The following events contain mistakes:", "Seuraavat tapahtumat sis\xE4lsiv\xE4t virheit\xE4:")
    L(game_can_not_be_played, "The game can not be played:", "Peli ei ole pelattavissa:")
    
    // --------------------------------------------------------------------

    #undef L
#endif

#ifdef MULTI
    #ifdef CREATE_LISTS
        #define L(ID, ENG, FIN)                                         \
        static constexpr char* s_##ID##_FIN[] = FIN;                    \
        static constexpr char* s_##ID##_ENG[] = ENG;                    
    #else
        
        #ifdef FILL_LOC_IDENTIFIER
            #define L(ID, ENG, FIN) ID##,
    
        #else
            #define L(ID, ENG, FI) case Loc_List_Identifier::##ID:      \
            {                                                           \
                switch(s_settings.language)                             \
                {                                                       \
                    case Language::english:                             \
                    {                                                   \
                        result.list = (char**)s_##ID##_ENG;             \
                        result.count = Array_Lenght(s_##ID##_ENG);      \
                    }break;                                             \
                                                                        \
                    case Language::finnish:                             \
                    {                                                   \
                        result.list = (char**)s_##ID##_FIN;             \
                        result.count = Array_Lenght(s_##ID##_FIN);      \
                    }break;                                             \
                }                                                       \
            }break;
        #endif
    #endif
        
    #define E ,
    
    L(main_menu_buttons,
        {
            "Continue" E
            "New Game" E
            "Load Game" E
            "Open Editor" E
            "Settings" E
            "Close"
        }, 
        {
            "Jatka" E
            "Uusi Peli" E
            "Lataa Peli" E
            "Avaa editori" E
            "Asetukset" E
            "Sulje"
        })
    
    L(languages,
        {
            "English" E
            "Finnish" E
        },
        {
            "Englanti" E
            "Suomi" E
        })

    #undef L
    #undef E
#endif