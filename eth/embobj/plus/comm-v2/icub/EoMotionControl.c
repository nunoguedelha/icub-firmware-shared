/*
 * Copyright (C) 2016 iCub Facility - Istituto Italiano di Tecnologia
 * Author:  Marco Accame
 * email:   marco.accame@iit.it
 * website: www.robotcub.org
 * Permission is granted to copy, distribute, and/or modify this program
 * under the terms of the GNU General Public License, version 2 or any
 * later version published by the Free Software Foundation.
 *
 * A copy of the license can be found at
 * http://www.robotcub.org/icub/license/gpl.txt
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
 * Public License for more details
*/

/* @file       EoMotionControl.c
    @brief      This file keeps ...
    @author     marco.accame@iit.it
    @date       Jul 19 2016
**/


// --------------------------------------------------------------------------------------------------------------------
// - external dependencies
// --------------------------------------------------------------------------------------------------------------------

#include "stdlib.h" 
#include "string.h"
#include "stdio.h"



// --------------------------------------------------------------------------------------------------------------------
// - declaration of extern public interface
// --------------------------------------------------------------------------------------------------------------------

#include "EoMotionControl.h"


// --------------------------------------------------------------------------------------------------------------------
// - declaration of extern hidden interface 
// --------------------------------------------------------------------------------------------------------------------
// empty-section


// --------------------------------------------------------------------------------------------------------------------
// - #define with internal scope
// --------------------------------------------------------------------------------------------------------------------
// empty-section


// --------------------------------------------------------------------------------------------------------------------
// - typedef with internal scope
// --------------------------------------------------------------------------------------------------------------------



// --------------------------------------------------------------------------------------------------------------------
// - declaration of static functions
// --------------------------------------------------------------------------------------------------------------------
// empty-section


// --------------------------------------------------------------------------------------------------------------------
// - definition (and initialisation) of static variables
// --------------------------------------------------------------------------------------------------------------------

static const eOmap_str_str_u08_t s_eomc_map_of_actuators[] =
{    
    {"foc", "eomc_act_foc", eomc_act_foc},
    {"mc4", "eomc_act_mc4", eomc_act_mc4},
    {"pwm", "eomc_act_pwm", eomc_act_pwm},

    {"none", "eomc_act_none", eomc_act_none},
    {"unknown", "eomc_act_unknown", eomc_act_unknown}
};  EO_VERIFYsizeof(s_eomc_map_of_actuators, (eomc_actuators_numberof+2)*sizeof(eOmap_str_str_u08_t));


static const eOmap_str_str_u08_t s_eomc_map_of_encoders[] =
{    
    {"aea", "eomc_enc_aea",eomc_enc_aea},
    {"amo", "eomc_enc_amo", eomc_enc_amo},
    {"qenc", "eomc_enc_qenc", eomc_enc_qenc},
    {"spichainof2", "eomc_enc_spichainof2", eomc_enc_spichainof2},
    {"absanalog", "eomc_enc_absanalog", eomc_enc_absanalog},
    {"mais", "eomc_enc_mais", eomc_enc_mais},
    {"spichainof3", "eomc_enc_spichainof3", eomc_enc_spichainof3},
    {"onfoc", "eomc_enc_onfoc", eomc_enc_onfoc},

    {"none", "eomc_enc_none", eomc_enc_none},
    {"unknown", "eomc_enc_unknown", eomc_enc_unknown}
};  EO_VERIFYsizeof(s_eomc_map_of_encoders, (eomc_encoders_numberof+2)*sizeof(eOmap_str_str_u08_t));


static const eOmap_str_str_u08_t s_eomc_map_of_positions[] =
{    
    {"atjoint", "eomc_pos_atjoint", eomc_pos_atjoint},
    {"atmotor", "eomc_pos_atmotor", eomc_pos_atmotor},
    
    {"none", "eomc_pos_none", eomc_pos_none},
    {"unknown", "eomc_pos_unknown", eomc_pos_unknown}
};  EO_VERIFYsizeof(s_eomc_map_of_positions, (eomc_positions_numberof+2)*sizeof(eOmap_str_str_u08_t));


static const eOmap_str_str_u08_t s_eomc_map_of_ctrlboards[] =
{    
    {"DONTCARE", "eomc_ctrlboard_DONTCARE", eomc_ctrlboard_DONTCARE},
    {"NO_CONTROL", "eomc_ctrlboard_NO_CONTROL", eomc_ctrlboard_NO_CONTROL},
    {"ANKLE", "eomc_ctrlboard_ANKLE", eomc_ctrlboard_ANKLE},
    {"UPPERLEG", "eomc_ctrlboard_UPPERLEG", eomc_ctrlboard_UPPERLEG},
    {"WAIST", "eomc_ctrlboard_WAIST", eomc_ctrlboard_WAIST},
    {"SHOULDER", "eomc_ctrlboard_SHOULDER", eomc_ctrlboard_SHOULDER},
    {"HEAD_neckpitch_neckroll", "eomc_ctrlboard_HEAD_neckpitch_neckroll", eomc_ctrlboard_HEAD_neckpitch_neckroll},
    {"HEAD_neckyaw_eyes", "eomc_ctrlboard_HEAD_neckyaw_eyes", eomc_ctrlboard_HEAD_neckyaw_eyes},
    {"FACE_eyelids_jaw", "eomc_ctrlboard_FACE_eyelids_jaw", eomc_ctrlboard_FACE_eyelids_jaw},
    {"4jointsNotCoupled", "eomc_ctrlboard_4jointsNotCoupled", eomc_ctrlboard_4jointsNotCoupled},
    {"HAND_thumb", "eomc_ctrlboard_HAND_thumb", eomc_ctrlboard_HAND_thumb},
    {"HAND_2", "eomc_ctrlboard_HAND_2", eomc_ctrlboard_HAND_2},
    {"FOREARM", "eomc_ctrlboard_FOREARM", eomc_ctrlboard_FOREARM},
    {"CER_LOWER_ARM", "eomc_ctrlboard_CER_LOWER_ARM", eomc_ctrlboard_CER_LOWER_ARM},
    {"CER_HAND", "eomc_ctrlboard_CER_HAND", eomc_ctrlboard_CER_HAND},
    {"CER_WAIST", "eomc_ctrlboard_CER_WAIST", eomc_ctrlboard_CER_WAIST},
    {"CER_UPPER_ARM", "eomc_ctrlboard_CER_UPPER_ARM", eomc_ctrlboard_CER_UPPER_ARM},
    {"CER_BASE", "eomc_ctrlboard_CER_BASE", eomc_ctrlboard_CER_BASE},
    {"CER_NECK", "eomc_ctrlboard_CER_NECK", eomc_ctrlboard_CER_NECK},
    
    {"none", "eomc_ctrlboard_none", eomc_ctrlboard_none},
    {"unknown", "eomc_ctrlboard_unknown", eomc_ctrlboard_unknown}
};  EO_VERIFYsizeof(s_eomc_map_of_ctrlboards, (eomc_ctrlboards_numberof+2)*sizeof(eOmap_str_str_u08_t));


// --------------------------------------------------------------------------------------------------------------------
// - definition (and initialisation) of extern variables
// --------------------------------------------------------------------------------------------------------------------
// empty-section


// --------------------------------------------------------------------------------------------------------------------
// - definition of extern public functions
// --------------------------------------------------------------------------------------------------------------------


extern const char * eomc_actuator2string(eOmc_actuator_t actuator, eObool_t usecompactstring)
{
    const eOmap_str_str_u08_t * map = s_eomc_map_of_actuators;
    const uint8_t size = eomc_actuators_numberof+2;
    const uint8_t value = actuator;
    const char * str = eo_common_map_str_str_u08__value2string(map, size, value, usecompactstring);
    
    if(NULL == str)
    {
        str = (eobool_true == usecompactstring) ? (map[size-1].str0) : (map[size-1].str1);
    }
    
    return(str);    
}


extern eOmc_actuator_t eomc_string2actuator(const char * string, eObool_t usecompactstring)
{
    const eOmap_str_str_u08_t * map = s_eomc_map_of_actuators;
    const uint8_t size = eomc_actuators_numberof+2;
    const uint8_t defvalue = eomc_act_unknown;
    
    return((eOmc_actuator_t)eo_common_map_str_str_u08__string2value(map, size, string, usecompactstring, defvalue));
}


extern const char * eomc_encoder2string(eOmc_encoder_t encoder, eObool_t usecompactstring)
{
    const eOmap_str_str_u08_t * map = s_eomc_map_of_encoders;
    const uint8_t size = eomc_encoders_numberof+2;
    const uint8_t value = encoder;
    const char * str = eo_common_map_str_str_u08__value2string(map, size, value, usecompactstring);
    
    if(NULL == str)
    {
        str = (eobool_true == usecompactstring) ? (map[size-1].str0) : (map[size-1].str1);
    }
    
    return(str);    
}


extern eOmc_encoder_t eomc_string2encoder(const char * string, eObool_t usecompactstring)
{
    const eOmap_str_str_u08_t * map = s_eomc_map_of_encoders;
    const uint8_t size = eomc_encoders_numberof+2;
    const uint8_t defvalue = eomc_enc_unknown;
    
    return((eOmc_encoder_t)eo_common_map_str_str_u08__string2value(map, size, string, usecompactstring, defvalue));
}


extern const char * eomc_position2string(eOmc_position_t position, eObool_t usecompactstring)
{
    const eOmap_str_str_u08_t * map = s_eomc_map_of_positions;
    const uint8_t size = eomc_positions_numberof+2;
    const uint8_t value = position;
    const char * str = eo_common_map_str_str_u08__value2string(map, size, value, usecompactstring);
    
    if(NULL == str)
    {
        str = (eobool_true == usecompactstring) ? (map[size-1].str0) : (map[size-1].str1);
    }
    
    return(str);   
}


extern eOmc_position_t eomc_string2position(const char * string, eObool_t usecompactstring)
{
    const eOmap_str_str_u08_t * map = s_eomc_map_of_positions;
    const uint8_t size = eomc_positions_numberof+2;
    const uint8_t defvalue = eomc_pos_unknown; 
    
    return((eOmc_position_t)eo_common_map_str_str_u08__string2value(map, size, string, usecompactstring, defvalue));    
}


extern uint8_t eomc_encoder_get_numberofcomponents(eOmc_encoder_t encoder)
{
    uint8_t ret = 0;
    
    switch(encoder)
    {
        
        case eomc_enc_aea:
        case eomc_enc_amo:
        case eomc_enc_qenc: 
        case eomc_enc_absanalog:
        case eomc_enc_mais:    
        case eomc_enc_onfoc:
        {
            ret = 1;
        } break;
    
        case eomc_enc_spichainof2:
        {
            ret = 2;
        } break;
  
        case eomc_enc_spichainof3:
        {
            ret = 3;
        } break;

        default:
        {
            ret = 0;
        } break;
    } 
    
    return(ret);
}

extern eOmc_ctrlboard_t eomc_string2controllerboard(const char * string, eObool_t usecompactstring)
{
    const eOmap_str_str_u08_t * map = s_eomc_map_of_ctrlboards;
    const uint8_t size = eomc_ctrlboards_numberof+2;
    const uint8_t defvalue = eomc_ctrlboard_unknown;
    
    return((eOmc_ctrlboard_t)eo_common_map_str_str_u08__string2value(map, size, string, usecompactstring, defvalue));
}



// --------------------------------------------------------------------------------------------------------------------
// - definition of extern hidden functions 
// --------------------------------------------------------------------------------------------------------------------
// empty-section


// --------------------------------------------------------------------------------------------------------------------
// - definition of static functions 
// --------------------------------------------------------------------------------------------------------------------
// empty-section

// --------------------------------------------------------------------------------------------------------------------
// - end-of-file (leave a blank line after)
// --------------------------------------------------------------------------------------------------------------------


