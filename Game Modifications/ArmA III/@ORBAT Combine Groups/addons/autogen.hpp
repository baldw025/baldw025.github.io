class CfgFactionClasses {
    class TU_CMB {
        displayName = "Universal Union (Combine)";
        side = 0;
        flag = "cmb_flag_co.paa";
        icon = "cmb_co.paa";
        priority = -6;
    };
};

class CfgGroups {
    class EAST {

        class TU_CMB {
            name = "Universal Union (Combine)";

            class Infantry {
                name = "Infantry";

                class cmb_o_tucmb_infantry_civil_protection {
                    name = "Civil Protection";
                    side = 0;
                    faction = "TU_CMB";
                    icon = "\A3\ui_f\data\map\markers\nato\o_inf.paa";
                    rarityGroup = 0.5;

                    class Unit0 {
                        position[] = {0,0,0};
                        rank = "SERGEANT";
                        side = 0;
                        vehicle = "TU_CMB_CPOfficer_F";
                    };
                    class Unit1 {
                        position[] = {5,-5,0};
                        rank = "PRIVATE";
                        side = 0;
                        vehicle = "TU_CMB_CPOfficer_F";
                    };
                    class Unit2 {
                        position[] = {-5,-5,0};
                        rank = "PRIVATE";
                        side = 0;
                        vehicle = "TU_CMB_CPOfficer_F";
                    };
                    class Unit3 {
                        position[] = {10,-10,0};
                        rank = "PRIVATE";
                        side = 0;
                        vehicle = "TU_CMB_CPOfficer_F";
                    };
                    class Unit4 {
                        position[] = {-10,-10,0};
                        rank = "PRIVATE";
                        side = 0;
                        vehicle = "TU_CMB_CPOfficer_F";
                    };
                    class Unit5 {
                        position[] = {15,-15,0};
                        rank = "PRIVATE";
                        side = 0;
                        vehicle = "TU_CMB_CPOfficer_F";
                    };
                };

                class cmb_o_tucmb_infantry_combine_soldiers {
                    name = "Combine Soldiers";
                    side = 0;
                    faction = "TU_CMB";
                    icon = "\A3\ui_f\data\map\markers\nato\o_inf.paa";
                    rarityGroup = 0.5;

                    class Unit0 {
                        position[] = {0,0,0};
                        rank = "SERGEANT";
                        side = 0;
                        vehicle = "TU_CMB_OESoldier_F";
                    };
                    class Unit1 {
                        position[] = {5,-5,0};
                        rank = "PRIVATE";
                        side = 0;
                        vehicle = "TU_CMB_OSoldier_F";
                    };
                    class Unit2 {
                        position[] = {-5,-5,0};
                        rank = "PRIVATE";
                        side = 0;
                        vehicle = "TU_CMB_OSoldier_F";
                    };
                    class Unit3 {
                        position[] = {10,-10,0};
                        rank = "PRIVATE";
                        side = 0;
                        vehicle = "TU_CMB_OSoldier_F";
                    };
                    class Unit4 {
                        position[] = {-10,-10,0};
                        rank = "PRIVATE";
                        side = 0;
                        vehicle = "TU_CMB_OSoldier_F";
                    };
                    class Unit5 {
                        position[] = {15,-15,0};
                        rank = "PRIVATE";
                        side = 0;
                        vehicle = "TU_CMB_OSoldier_F";
                    };
                    class Unit6 {
                        position[] = {-15,-15,0};
                        rank = "PRIVATE";
                        side = 0;
                        vehicle = "TU_CMB_OSoldier_F";
                    };
                    class Unit7 {
                        position[] = {20,-20,0};
                        rank = "PRIVATE";
                        side = 0;
                        vehicle = "TU_CMB_OSoldier_F";
                    };
                    class Unit8 {
                        position[] = {-20,-20,0};
                        rank = "PRIVATE";
                        side = 0;
                        vehicle = "TU_CMB_OSoldier_F";
                    };
                };

            };

            class SpecOps {
                name = "Special Forces";

                class cmb_o_tucmb_infantry_combine_platoon {
                    name = "Combine Platoon";
                    side = 0;
                    faction = "TU_CMB";
                    icon = "\A3\ui_f\data\map\markers\nato\o_inf.paa";
                    rarityGroup = 0.5;

                    class Unit0 {
                        position[] = {0,0,0};
                        rank = "CAPTAIN";
                        side = 0;
                        vehicle = "TU_CMB_OOfficer_F";
                    };
                    class Unit1 {
                        position[] = {5,-5,0};
                        rank = "LIEUTENANT";
                        side = 0;
                        vehicle = "TU_CMB_OESoldier_F";
                    };
                    class Unit2 {
                        position[] = {-5,-5,0};
                        rank = "PRIVATE";
                        side = 0;
                        vehicle = "TU_CMB_OSoldier_F";
                    };
                    class Unit3 {
                        position[] = {10,-10,0};
                        rank = "PRIVATE";
                        side = 0;
                        vehicle = "TU_CMB_OSoldier_F";
                    };
                    class Unit4 {
                        position[] = {-10,-10,0};
                        rank = "PRIVATE";
                        side = 0;
                        vehicle = "TU_CMB_OSoldier_F";
                    };
                    class Unit5 {
                        position[] = {15,-15,0};
                        rank = "PRIVATE";
                        side = 0;
                        vehicle = "TU_CMB_OSoldier_F";
                    };
                    class Unit6 {
                        position[] = {-15,-15,0};
                        rank = "PRIVATE";
                        side = 0;
                        vehicle = "TU_CMB_OSoldier_F";
                    };
                    class Unit7 {
                        position[] = {20,-20,0};
                        rank = "PRIVATE";
                        side = 0;
                        vehicle = "TU_CMB_OSoldier_F";
                    };
                    class Unit8 {
                        position[] = {-20,-20,0};
                        rank = "PRIVATE";
                        side = 0;
                        vehicle = "TU_CMB_OSoldier_F";
                    };
                };

                class cmb_o_tucmb_specops_nova_prospekt {
                    name = "Nova Prospekt";
                    side = 0;
                    faction = "TU_CMB";
                    icon = "\A3\ui_f\data\map\markers\nato\o_recon.paa";
                    rarityGroup = 0.5;

                    class Unit0 {
                        position[] = {0,0,0};
                        rank = "SERGEANT";
                        side = 0;
                        vehicle = "TU_CMB_OOfficer_F_NP";
                    };
                    class Unit1 {
                        position[] = {5,-5,0};
                        rank = "PRIVATE";
                        side = 0;
                        vehicle = "TU_CMB_OSoldier_F_NP";
                    };
                    class Unit2 {
                        position[] = {-5,-5,0};
                        rank = "PRIVATE";
                        side = 0;
                        vehicle = "TU_CMB_OSoldier_F_NP";
                    };
                    class Unit3 {
                        position[] = {10,-10,0};
                        rank = "PRIVATE";
                        side = 0;
                        vehicle = "TU_CMB_OSoldier_F_NP";
                    };
                    class Unit4 {
                        position[] = {-10,-10,0};
                        rank = "PRIVATE";
                        side = 0;
                        vehicle = "TU_CMB_OSoldier_F_NP";
                    };
                    class Unit5 {
                        position[] = {15,-15,0};
                        rank = "PRIVATE";
                        side = 0;
                        vehicle = "TU_CMB_OSoldier_F_NP";
                    };
                };

            };

            class Motorized {
                name = "Motorized Infantry";

                class cmb_o_tucmb_motorized_combine_apcs {
                    name = "Combine APCs";
                    side = 0;
                    faction = "TU_CMB";
                    icon = "\A3\ui_f\data\map\markers\nato\o_motor_inf.paa";
                    rarityGroup = 0.5;

                    class Unit0 {
                        position[] = {0,0,0};
                        rank = "SERGEANT";
                        side = 0;
                        vehicle = "Veh_TU_CMB_APC_F";
                    };
                    class Unit1 {
                        position[] = {5,-8,0};
                        rank = "PRIVATE";
                        side = 0;
                        vehicle = "Veh_TU_CMB_APC_F";
                    };
                };

            };

            class Motorized_MTP {
                name = "Motorized Infantry (MTP)";

            };

            class Support {
                name = "Support Infantry";

            };

            class Mechanized {
                name = "Mechanized Infantry";

            };

            class Armored {
                name = "Armor";

            };

            class Artillery {
                name = "Artillery";

            };

            class Naval {
                name = "Naval";

            };

            class Air {
                name = "Air";

                class cmb_o_tucmb_air_combine_air_support {
                    name = "Combine Air Support";
                    side = 0;
                    faction = "TU_CMB";
                    icon = "\A3\ui_f\data\map\markers\nato\o_air.paa";
                    rarityGroup = 0.5;

                    class Unit0 {
                        position[] = {0,0,0};
                        rank = "SERGEANT";
                        side = 0;
                        vehicle = "TU_CMB_HunterChopper_F";
                    };
                    class Unit1 {
                        position[] = {30,-30,0};
                        rank = "PRIVATE";
                        side = 0;
                        vehicle = "TU_CMB_HunterChopper_F";
                    };
                };

            };


        };

    };
};