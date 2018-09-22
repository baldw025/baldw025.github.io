using System;
using System.Collections.Generic;
using GTA;
using GTA.Math;
using GTA.Native;

namespace SuperPunch
{
    public class SuperPunch : Script
    {
        private float force = 250.0f; //Change this to change the force applied

        public SuperPunch()
        {
            Tick += SuperPunch_Tick;
        }

        void SuperPunch_Tick(object sender, EventArgs e)
        {
            Ped player = Game.Player.Character;

            //Loop through all peds
            foreach (Ped ped in World.GetAllPeds())
            {
                //Check for damage by player
                if (Function.Call<bool>(Hash.HAS_ENTITY_BEEN_DAMAGED_BY_ENTITY, ped, player, true))
                {
                    //Check for damage by melee
                    if (Function.Call<bool>(Hash.HAS_PED_BEEN_DAMAGED_BY_WEAPON, ped, 0, 1))
                    {
                        //Get player direction
                        Vector3 direction = Vector3.Multiply(player.ForwardVector, force);

                        //Apply force to ped
                        ped.ApplyForce(direction);

                        //Clear all damage
                        Function.Call(Hash.CLEAR_ENTITY_LAST_DAMAGE_ENTITY, ped);

                        //Break loop
                        break;
                    }
                }
            }
			foreach (Vehicle vehicle in World.GetAllVehicles())
			{
				//Check for damage by player
				if (Function.Call<bool>(Hash.HAS_ENTITY_BEEN_DAMAGED_BY_ENTITY, vehicle, player, true))
				{
					if (Function.Call<bool>(Hash.HAS_ENTITY_BEEN_DAMAGED_BY_WEAPON, vehicle, 0, 1))
                    {
                        //Get player direction
                        Vector3 direction = Vector3.Multiply(player.ForwardVector, force);

                        //Apply force to ped
                        vehicle.ApplyForce(direction);

                        //Clear all damage
                        Function.Call(Hash.CLEAR_ENTITY_LAST_DAMAGE_ENTITY, vehicle);

                        //Break loop
                        break;
                    }
                }
			}
        }
    }
}