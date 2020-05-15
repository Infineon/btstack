/*
 * $ Copyright Cypress Semiconductor $
 */

/** @file
 *
 * Defines the utilities used by the A2DP sink for configuring the audio data path for streaming
 */
#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @addtogroup  wicedbt_a2dp        Advanced Audio Distribution Profile (A2DP) Sink
 * @ingroup     wicedbt_av
 * @{
 */


/******************************************************
 *                 Type Definitions
 ******************************************************/

/** Play Status Indication Callback. This will be invoked when there is a change in the play status
 *     Play status values
 *           JITTER_IDLE_STATE  0x1
 *           JITTER_NORMAL_STATE 0x2
 *           JITTER_UNDERRUN_STATE  0x4
 *           JITTER_OVERRUN_STATE 0x8
 */
typedef void (*wiced_audio_play_status_ind_t)( uint8_t play_status);


/*************************************************************
 *                 Function Declarations
 *************************************************************/

/** Wiced audio sink initialization
 *
 *  @param p_param    pointer to the tuning parameters
 *
 *  @return wiced_result_t (WICED_BT_XXX)
 */
wiced_result_t wiced_audio_sink_config_init( wiced_bt_a2dp_sink_audio_tuning_params_t* p_param );

/** API to configure the sink to perform SBC decoding and to route the decoded
 * audio data over I2S or UART on starting the streaming
 *
 *Called by the application when the streaming is to be started
 *
 *  @param handle  AVDT connection handle
 *
 *  @param audio_route - Audio route to be used to send the decoded audio data,
 *                                 I2S or UART
 *
 *  @param cp_type  Content protection type. Refer AVDT_CP_TYPE defined in wiced_bt_avdt.h
 *
 *  @param p_codec_info    Codec information
 *
 *  @return wiced_result_t (WICED_BT_XXX)
 */
wiced_result_t wiced_audio_sink_configure( uint16_t handle, uint32_t is_master, uint32_t audio_route, uint16_t cp_type,wiced_bt_a2dp_codec_info_t* p_codec_info );

/** API to reset the sink on stopping/suspending the streaming
 *
 *Called by the application when the streaming is stopped/suspended
 *
 *  @param handle  AVDT connection handle
 *
 *  @return wiced_result_t (WICED_BT_XXX)
 */
wiced_result_t wiced_audio_sink_reset( uint16_t handle );

/** To mute/unmute the audio
 *
 *Called by the application to mute the audio when playing the music. Application shall
 * this function to unmute also to restart playing the music
 *
 *  @param enable    1 to mute, 0 to unmute
 *
 *  @param ramp_ms    ramp up/down time in milli seconds
 *
 *  @return wiced_result_t (WICED_BT_XXX)
 */
wiced_result_t wiced_audio_sink_mute( wiced_bool_t enable, uint16_t ramp_ms );

/**
 *  Function         wiced_audio_set_i2s_out_sf
 *
 *  API to configure output I2S sampling frequency
 *
 *  Called by the application before starting the streaming
 *
 *  @param out_sf  Desired output i2s sampling frequency (ex. 16000/32000/44100/48000)
 *
 *  @return wiced_bool_t  TRUE in success case otherwise FALSE
 *
 *  NOTE : This API must be called before calling the API wiced_audio_sink_configure
 */
wiced_bool_t wiced_audio_set_i2s_out_sf(uint32_t out_sf);

/**
 *  Function         wiced_audio_register_play_status_ind_cback
 *
 *  Debug API to  register for play status indication
 *
 *  Called by the application before starting the streaming
 *
 *  @param[in] cback : Callback function to be invoked on play status change
 *
 *  @return None
 *
 */
void wiced_audio_register_play_status_ind_cback( wiced_audio_play_status_ind_t cback );

/**
 *  Function         wiced_audio_get_jitter_buffer_state
 *
 *  Debug API to get the jitter buffer state
 *
 *  @param[out] p_current_buf_ms : current jitter buffer size in msec
 *
 *  @param[out] p_clk_tuning : current clock tuning value
 *
 *  @return None
 *
 */
void wiced_audio_get_jitter_buffer_state( uint16_t* p_current_buf_ms, uint16_t* p_clk_tuning );

/** @} */ // end of wiced_audio_sink

#ifdef __cplusplus
} /*extern "C" */
#endif


