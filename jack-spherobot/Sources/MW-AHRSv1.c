/*
 * MW-AHRSv1.c
 *
 *  Created on: 2016. 4. 30.
 *      Author: Suhan Park
 */

#include <string.h>
#include "MW-AHRSv1.h"


void mw_ahrs_input_data(MW_AHRS *dst)
{
	if(dst->can_read_data[0] == 0xF0)
	{
		switch(dst->can_read_data[1])
		{
		case ACCELERATION:
			memcpy(dst->a_raw_data, &dst->can_read_data[2],6);
			dst->a_x = GET_S16_BYTE(dst->a_raw_data[0], dst->a_raw_data[1]) / 1000.0f;
			dst->a_y = GET_S16_BYTE(dst->a_raw_data[2], dst->a_raw_data[3]) / 1000.0f;
			dst->a_z = GET_S16_BYTE(dst->a_raw_data[4], dst->a_raw_data[5]) / 1000.0f;
			break;
		case GYROSCOPE:
			memcpy(dst->g_raw_data, &dst->can_read_data[2],6);
			dst->g_x = GET_S16_BYTE(dst->g_raw_data[0], dst->g_raw_data[1]) / 10.0f;
			dst->g_y = GET_S16_BYTE(dst->g_raw_data[2], dst->g_raw_data[3]) / 10.0f;
			dst->g_z = GET_S16_BYTE(dst->g_raw_data[4], dst->g_raw_data[5]) / 10.0f;
			break;
		case ANGLE:
			memcpy(dst->e_raw_data, &dst->can_read_data[2],6);
			dst->e_roll = GET_S16_BYTE(dst->e_raw_data[0], dst->e_raw_data[1]) / 100.0f;
			dst->e_pitch = GET_S16_BYTE(dst->e_raw_data[2], dst->e_raw_data[3]) / 100.0f;
			dst->e_yaw = GET_S16_BYTE(dst->e_raw_data[4], dst->e_raw_data[5]) / 100.0f;
			break;
		case MAGNETIC:
			memcpy(dst->m_raw_data, &dst->can_read_data[2],6);
			dst->m_x = GET_S16_BYTE(dst->m_raw_data[0], dst->m_raw_data[1]) / 10.0f;
			dst->m_y = GET_S16_BYTE(dst->m_raw_data[2], dst->m_raw_data[3]) / 10.0f;
			dst->m_z = GET_S16_BYTE(dst->m_raw_data[4], dst->m_raw_data[5]) / 10.0f;
			break;
		}
	}
}

void mw_ahrs_set_data_type(MW_AHRS *dst, uint8_t acc, uint8_t gyro, uint8_t angle, uint8_t mangetic)
{
	// 18 16 00 00    07 00 00 00
	dst->can_write_data[0] = AC_OBJECT_WRITE_REQ+OT_INT32;
	dst->can_write_data[1] = SET_CAN_DATA;
	dst->can_write_data[2] = 0;
	dst->can_write_data[3] = 0;

	dst->can_write_data[4] = (acc << DT_ACC) + (gyro << DT_GYRO) +
							(angle << DT_ANGLE) + (mangetic << DT_MAGNETIC);
	dst->can_write_data[5] = 0;
	dst->can_write_data[6] = 0;
	dst->can_write_data[7] = 0;
}

void mw_ahrs_set_period(MW_AHRS *dst, uint32_t time)
{
	dst->can_write_data[0] = AC_OBJECT_WRITE_REQ+OT_INT32;
	dst->can_write_data[1] = SET_PERIOD;
	dst->can_write_data[2] = 0;
	dst->can_write_data[3] = 0;

	dst->can_write_data[4] = GET_LOWBYTE_16(GET_LOWWORD_32(time));
	dst->can_write_data[5] = GET_HIGHBYTE_16(GET_LOWWORD_32(time));
	dst->can_write_data[6] = GET_LOWBYTE_16(GET_HIGHWORD_32(time));
	dst->can_write_data[7] = GET_HIGHBYTE_16(GET_HIGHWORD_32(time));
}
