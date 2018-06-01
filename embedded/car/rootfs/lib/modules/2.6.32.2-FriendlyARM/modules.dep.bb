net/mac80211/mac80211.ko symbol:ieee80211_free_hw symbol:ieee80211_unregister_hw symbol:ieee80211_register_hw symbol:ieee80211_alloc_hw symbol:ieee80211_restart_hw symbol:ieee80211_tx_status symbol:ieee80211_tx_status_irqsafe symbol:ieee80211_sta_block_awake symbol:ieee80211_find_sta symbol:ieee80211_find_sta_by_hw symbol:ieee80211_scan_completed symbol:ieee80211_stop_tx_ba_cb_irqsafe symbol:ieee80211_stop_tx_ba_session symbol:ieee80211_start_tx_ba_cb_irqsafe symbol:ieee80211_start_tx_ba_session symbol:ieee80211_cqm_rssi_notify symbol:ieee80211_connection_loss symbol:ieee80211_beacon_loss symbol:ieee80211_disable_dyn_ps symbol:ieee80211_enable_dyn_ps symbol:ieee80211_chswitch_done symbol:rate_control_send_low symbol:ieee80211_rate_control_unregister symbol:ieee80211_rate_control_register symbol:ieee80211_get_tkip_key symbol:ieee80211_rx_irqsafe symbol:ieee80211_rx symbol:ieee80211_get_buffered_bc symbol:ieee80211_ctstoself_get symbol:ieee80211_rts_get symbol:ieee80211_probereq_get symbol:ieee80211_nullfunc_get symbol:ieee80211_pspoll_get symbol:ieee80211_beacon_get_tim symbol:ieee80211_queue_delayed_work symbol:ieee80211_queue_work symbol:ieee80211_wake_queues symbol:ieee80211_queue_stopped symbol:ieee80211_stop_queues symbol:ieee80211_stop_queue symbol:ieee80211_wake_queue symbol:ieee80211_ctstoself_duration symbol:ieee80211_rts_duration symbol:ieee80211_generic_frame_duration symbol:wiphy_to_ieee80211_hw symbol:ieee80211_iterate_active_interfaces_atomic symbol:ieee80211_iterate_active_interfaces symbol:__ieee80211_get_rx_led_name symbol:__ieee80211_get_tx_led_name symbol:__ieee80211_get_assoc_led_name symbol:__ieee80211_get_radio_led_name
cfg80211

net/wireless/cfg80211.ko symbol:wiphy_rfkill_set_hw_state symbol:wiphy_free symbol:wiphy_unregister symbol:wiphy_rfkill_stop_polling symbol:wiphy_rfkill_start_polling symbol:wiphy_register symbol:wiphy_new symbol:ieee80211_radiotap_iterator_next symbol:ieee80211_radiotap_iterator_init symbol:ieee80211_bss_get_ie symbol:cfg80211_classify8021d symbol:ieee80211_amsdu_to_8023s symbol:ieee80211_data_from_8023 symbol:ieee80211_data_to_8023 symbol:ieee80211_get_hdrlen_from_skb symbol:ieee80211_hdrlen symbol:bridge_tunnel_header symbol:rfc1042_header symbol:__ieee80211_get_channel symbol:ieee80211_frequency_to_channel symbol:ieee80211_channel_to_frequency symbol:ieee80211_get_response_rate symbol:regulatory_hint symbol:wiphy_apply_custom_regulatory symbol:freq_reg_info symbol:cfg80211_unlink_bss symbol:cfg80211_put_bss symbol:cfg80211_inform_bss_frame symbol:cfg80211_inform_bss symbol:cfg80211_get_mesh symbol:cfg80211_get_bss symbol:cfg80211_find_ie symbol:cfg80211_scan_done symbol:cfg80211_wext_giwscan symbol:cfg80211_wext_siwscan symbol:cfg80211_cqm_rssi_notify symbol:cfg80211_action_tx_status symbol:cfg80211_rx_action symbol:cfg80211_new_sta symbol:cfg80211_remain_on_channel_expired symbol:cfg80211_ready_on_channel symbol:cfg80211_michael_mic_failure symbol:cfg80211_send_assoc_timeout symbol:cfg80211_send_auth_timeout symbol:__cfg80211_auth_canceled symbol:cfg80211_send_disassoc symbol:__cfg80211_send_disassoc symbol:cfg80211_send_deauth symbol:__cfg80211_send_deauth symbol:cfg80211_send_rx_assoc symbol:cfg80211_send_rx_auth symbol:cfg80211_ibss_joined symbol:cfg80211_disconnected symbol:cfg80211_roamed symbol:cfg80211_connect_result symbol:cfg80211_wext_giwessid symbol:cfg80211_wext_siwessid symbol:cfg80211_wext_giwap symbol:cfg80211_wext_siwap symbol:cfg80211_wireless_stats symbol:cfg80211_wext_giwrate symbol:cfg80211_wext_siwrate symbol:cfg80211_wext_giwpower symbol:cfg80211_wext_siwpower symbol:cfg80211_wext_giwauth symbol:cfg80211_wext_siwauth symbol:cfg80211_wext_giwtxpower symbol:cfg80211_wext_siwtxpower symbol:cfg80211_wext_giwfreq symbol:cfg80211_wext_siwfreq symbol:cfg80211_wext_giwencode symbol:cfg80211_wext_siwencodeext symbol:cfg80211_wext_siwencode symbol:cfg80211_wext_giwretry symbol:cfg80211_wext_siwretry symbol:cfg80211_wext_giwfrag symbol:cfg80211_wext_siwfrag symbol:cfg80211_wext_giwrts symbol:cfg80211_wext_siwrts symbol:cfg80211_wext_giwrange symbol:cfg80211_wext_giwmode symbol:cfg80211_wext_siwmode symbol:cfg80211_wext_giwname symbol:cfg80211_wext_siwmlme symbol:cfg80211_wext_siwgenie

net/wireless/lib80211_crypt_ccmp.ko
lib80211

net/wireless/lib80211_crypt_wep.ko
lib80211

net/wireless/lib80211.ko symbol:lib80211_get_crypto_ops symbol:lib80211_unregister_crypto_ops symbol:lib80211_register_crypto_ops symbol:lib80211_crypt_delayed_deinit symbol:lib80211_crypt_deinit_handler symbol:lib80211_crypt_quiescing symbol:lib80211_crypt_deinit_entries symbol:lib80211_crypt_info_free symbol:lib80211_crypt_info_init symbol:print_ssid

net/wireless/lib80211_crypt_tkip.ko
lib80211

net/bluetooth/l2cap.ko bt-proto-0 symbol:l2cap_load
bluetooth

net/bluetooth/sco.ko bt-proto-2
bluetooth

net/bluetooth/bluetooth.ko net-pf-31 symbol:bt_sock_wait_state symbol:bt_sock_ioctl symbol:bt_sock_poll symbol:bt_sock_recvmsg symbol:bt_accept_dequeue symbol:bt_accept_unlink symbol:bt_accept_enqueue symbol:bt_sock_unlink symbol:bt_sock_link symbol:bt_sock_unregister symbol:bt_sock_register symbol:hci_send_sco symbol:hci_send_acl symbol:hci_unregister_cb symbol:hci_register_cb symbol:hci_unregister_proto symbol:hci_register_proto symbol:hci_recv_fragment symbol:hci_recv_frame symbol:hci_resume_dev symbol:hci_suspend_dev symbol:hci_unregister_dev symbol:hci_register_dev symbol:hci_free_dev symbol:hci_alloc_dev symbol:hci_conn_put_device symbol:hci_conn_hold_device symbol:hci_conn_switch_role symbol:hci_conn_change_link_key symbol:hci_conn_security symbol:hci_conn_check_link_mode symbol:hci_connect symbol:hci_get_route symbol:bt_debugfs symbol:bt_err symbol:batostr symbol:baswap

net/bluetooth/rfcomm/rfcomm.ko bt-proto-3
bluetooth l2cap

net/bluetooth/hidp/hidp.ko bt-proto-6
bluetooth l2cap

net/bluetooth/bnep/bnep.ko bt-proto-4
bluetooth l2cap

compat/compat_firmware_class.ko symbol:compat_request_firmware_nowait symbol:compat_request_firmware symbol:compat_release_firmware

compat/compat.ko

drivers/net/wireless/rtl818x/rtl8187.ko usb:v1737p0073d*dc*dsc*dp*ic*isc*ip* usb:v1B75p8187d*dc*dsc*dp*ic*isc*ip* usb:v18E8p6232d*dc*dsc*dp*ic*isc*ip* usb:v13D1pABE6d*dc*dsc*dp*ic*isc*ip* usb:v1371p9401d*dc*dsc*dp*ic*isc*ip* usb:v114Bp0150d*dc*dsc*dp*ic*isc*ip* usb:v0DF6p0029d*dc*dsc*dp*ic*isc*ip* usb:v0DF6p0028d*dc*dsc*dp*ic*isc*ip* usb:v0DF6p000Dd*dc*dsc*dp*ic*isc*ip* usb:v03F0pCA02d*dc*dsc*dp*ic*isc*ip* usb:v0846p4260d*dc*dsc*dp*ic*isc*ip* usb:v0846p6A00d*dc*dsc*dp*ic*isc*ip* usb:v0846p6100d*dc*dsc*dp*ic*isc*ip* usb:v0789p010Cd*dc*dsc*dp*ic*isc*ip* usb:v0769p11F2d*dc*dsc*dp*ic*isc*ip* usb:v0BDAp8198d*dc*dsc*dp*ic*isc*ip* usb:v0BDAp8197d*dc*dsc*dp*ic*isc*ip* usb:v0BDAp8189d*dc*dsc*dp*ic*isc*ip* usb:v0BDAp8187d*dc*dsc*dp*ic*isc*ip* usb:v050Dp705Ed*dc*dsc*dp*ic*isc*ip* usb:v0B05p171Dd*dc*dsc*dp*ic*isc*ip*
mac80211 eeprom_93cx6 cfg80211

drivers/net/wireless/mac80211_hwsim.ko
mac80211 cfg80211

drivers/net/wireless/at76c50x-usb.ko usb:v03EBp7615d*dc*dsc*dp*ic*isc*ip* usb:v1557p0002d*dc*dsc*dp*ic*isc*ip* usb:v1690p0701d*dc*dsc*dp*ic*isc*ip* usb:v03EBp7617d*dc*dsc*dp*ic*isc*ip* usb:v03EBp7614d*dc*dsc*dp*ic*isc*ip* usb:v0DB0p1020d*dc*dsc*dp*ic*isc*ip* usb:v07AAp7613d*dc*dsc*dp*ic*isc*ip* usb:v12FDp1001d*dc*dsc*dp*ic*isc*ip* usb:v1915p2233d*dc*dsc*dp*ic*isc*ip* usb:v1371p0013d*dc*dsc*dp*ic*isc*ip* usb:v1371p0014d*dc*dsc*dp*ic*isc*ip* usb:v03EBp7613d*dc*dsc*dp*ic*isc*ip* usb:v03EBp7606d*dc*dsc*dp*ic*isc*ip* usb:v0D5CpA002d*dc*dsc*dp*ic*isc*ip* usb:v083Ap3501d*dc*dsc*dp*ic*isc*ip* usb:v05DDpFF35d*dc*dsc*dp*ic*isc*ip* usb:v07AAp0018d*dc*dsc*dp*ic*isc*ip* usb:v07AAp0011d*dc*dsc*dp*ic*isc*ip* usb:v049Fp0032d*dc*dsc*dp*ic*isc*ip* usb:v2019p3220d*dc*dsc*dp*ic*isc*ip* usb:v1044p8003d*dc*dsc*dp*ic*isc*ip* usb:v07B8pB000d*dc*dsc*dp*ic*isc*ip* usb:v050Dp0050d*dc*dsc*dp*ic*isc*ip* usb:v0681p001Bd*dc*dsc*dp*ic*isc*ip* usb:v0506p0A01d*dc*dsc*dp*ic*isc*ip* usb:v04A5p9001d*dc*dsc*dp*ic*isc*ip* usb:v1371p0002d*dc*dsc*dp*ic*isc*ip* usb:v1371p0001d*dc*dsc*dp*ic*isc*ip* usb:v1371p5743d*dc*dsc*dp*ic*isc*ip* usb:v03EBp4102d*dc*dsc*dp*ic*isc*ip* usb:v1668p7605d*dc*dsc*dp*ic*isc*ip* usb:v2001p3200d*dc*dsc*dp*ic*isc*ip* usb:v0864p4102d*dc*dsc*dp*ic*isc*ip* usb:v077Bp2227d*dc*dsc*dp*ic*isc*ip* usb:v077Bp2219d*dc*dsc*dp*ic*isc*ip* usb:v069Ap0321d*dc*dsc*dp*ic*isc*ip* usb:v03EBp7605d*dc*dsc*dp*ic*isc*ip* usb:v055DpA000d*dc*dsc*dp*ic*isc*ip* usb:v03EBp7604d*dc*dsc*dp*ic*isc*ip* usb:v069Ap0821d*dc*dsc*dp*ic*isc*ip* usb:v04BBp0919d*dc*dsc*dp*ic*isc*ip* usb:v0D8Ep7110d*dc*dsc*dp*ic*isc*ip* usb:v0D8Ep7100d*dc*dsc*dp*ic*isc*ip* usb:v8086p0200d*dc*dsc*dp*ic*isc*ip* usb:v05DDpFF31d*dc*dsc*dp*ic*isc*ip* usb:v04A5p9000d*dc*dsc*dp*ic*isc*ip* usb:v0D5CpA001d*dc*dsc*dp*ic*isc*ip* usb:v069Ap0320d*dc*dsc*dp*ic*isc*ip* usb:v0CDEp0001d*dc*dsc*dp*ic*isc*ip* usb:v03F0p011Cd*dc*dsc*dp*ic*isc*ip* usb:v0B3Bp1612d*dc*dsc*dp*ic*isc*ip* usb:v0864p4100d*dc*dsc*dp*ic*isc*ip* usb:v066Bp2211d*dc*dsc*dp*ic*isc*ip* usb:v03EBp7603d*dc*dsc*dp*ic*isc*ip*
mac80211 compat_firmware_class

drivers/net/wireless/libertas/libertas.ko symbol:__lbs_cmd symbol:lbs_host_sleep_cfg symbol:lbs_cmd_copyback symbol:lbs_notify_command_response symbol:lbs_queue_event symbol:lbs_stop_card symbol:lbs_start_card symbol:lbs_remove_card symbol:lbs_add_card symbol:lbs_resume symbol:lbs_suspend symbol:lbs_host_to_card_done symbol:lbs_debug symbol:lbs_process_rxed_packet symbol:lbs_send_tx_feedback
cfg80211

drivers/net/wireless/libertas/usb8xxx.ko usb:v05A3p8388d*dc*dsc*dp*ic*isc*ip* usb:v1286p2001d*dc*dsc*dp*ic*isc*ip*
compat_firmware_class libertas

drivers/net/wireless/libertas/libertas_sdio.ko sdio:c*v02DFd9104* sdio:c*v02DFd9103*
compat_firmware_class libertas

drivers/net/wireless/ath/ath.ko symbol:ath_rxbuf_alloc symbol:ath_regd_get_band_ctl symbol:ath_regd_init symbol:ath_reg_notifier_apply symbol:ath_is_world_regd symbol:ath_hw_setbssidmask
cfg80211

drivers/net/wireless/ath/ath9k/ath9k_htc.ko usb:v083ApA704d*dc*dsc*dp*ic*isc*ip* usb:v04CAp4605d*dc*dsc*dp*ic*isc*ip* usb:v13D3p3328d*dc*dsc*dp*ic*isc*ip* usb:v13D3p3327d*dc*dsc*dp*ic*isc*ip* usb:v07D1p3A10d*dc*dsc*dp*ic*isc*ip* usb:v0846p9018d*dc*dsc*dp*ic*isc*ip* usb:v0846p9030d*dc*dsc*dp*ic*isc*ip* usb:v0CF3p7015d*dc*dsc*dp*ic*isc*ip* usb:v0CF3p7010d*dc*dsc*dp*ic*isc*ip* usb:v0CF3p1006d*dc*dsc*dp*ic*isc*ip* usb:v0CF3p9271d*dc*dsc*dp*ic*isc*ip*
ath9k_hw compat_firmware_class mac80211 ath9k_common ath cfg80211

drivers/net/wireless/ath/ath9k/ath9k_common.ko symbol:ath9k_cmn_count_streams symbol:ath9k_cmn_key_delete symbol:ath9k_cmn_key_config symbol:ath9k_cmn_get_curchannel symbol:ath9k_cmn_update_ichannel symbol:ath9k_cmn_get_hw_crypto_keytype symbol:ath9k_cmn_padpos
ath9k_hw

drivers/net/wireless/ath/ath9k/ath9k_hw.ko symbol:ath9k_hw_name symbol:ath9k_hw_htc_resetinit symbol:ath_gen_timer_isr symbol:ath_gen_timer_free symbol:ath9k_hw_gen_timer_stop symbol:ath9k_hw_gen_timer_start symbol:ath_gen_timer_alloc symbol:ath9k_hw_gettsf32 symbol:ath9k_hw_set_tsfadjust symbol:ath9k_hw_reset_tsf symbol:ath9k_hw_settsf64 symbol:ath9k_hw_gettsf64 symbol:ath9k_hw_write_associd symbol:ath9k_hw_setmcastfilter symbol:ath9k_hw_setopmode symbol:ath9k_hw_set_txpowerlimit symbol:ath9k_hw_disable symbol:ath9k_hw_phy_disable symbol:ath9k_hw_setrxfilter symbol:ath9k_hw_getrxfilter symbol:ath9k_hw_setantenna symbol:ath9k_hw_getdefantenna symbol:ath9k_hw_set_gpio symbol:ath9k_hw_cfg_output symbol:ath9k_hw_gpio_get symbol:ath9k_hw_cfg_gpio_input symbol:ath9k_hw_set_sta_beacon_timers symbol:ath9k_hw_beaconinit symbol:ath9k_hw_setpower symbol:ath9k_hw_keyisvalid symbol:ath9k_hw_set_keycache_entry symbol:ath9k_hw_keysetmac symbol:ath9k_hw_keyreset symbol:ath9k_hw_reset symbol:ath9k_hw_check_alive symbol:ath9k_hw_deinit symbol:ath9k_hw_init_global_settings symbol:ath9k_hw_init symbol:ath9k_hw_computetxtime symbol:ath9k_hw_wait symbol:ar9003_hw_bb_watchdog_dbg_info symbol:ath9k_hw_getchan_noise symbol:ath9k_hw_reset_calvalid symbol:ath9k_hw_disable_mib_counters symbol:ath9k_hw_btcoex_disable symbol:ath9k_hw_btcoex_enable symbol:ath9k_hw_btcoex_set_weight symbol:ath9k_hw_btcoex_init_3wire symbol:ath9k_hw_btcoex_init_2wire symbol:ath9k_hw_init_btcoex_hw symbol:ath9k_hw_set_interrupts symbol:ath9k_hw_intrpend symbol:ath9k_hw_beaconq_setup symbol:ath9k_hw_stopdmarecv symbol:ath9k_hw_abortpcurecv symbol:ath9k_hw_stoppcurecv symbol:ath9k_hw_startpcureceive symbol:ath9k_hw_putrxbuf symbol:ath9k_hw_setrxabort symbol:ath9k_hw_rxprocdesc symbol:ath9k_hw_resettxqueue symbol:ath9k_hw_releasetxqueue symbol:ath9k_hw_setuptxqueue symbol:ath9k_hw_get_txq_props symbol:ath9k_hw_set_txq_props symbol:ath9k_hw_gettxintrtxqs symbol:ath9k_hw_stoptxdma symbol:ath9k_hw_updatetxtriglevel symbol:ath9k_hw_numtxpending symbol:ath9k_hw_cleartxdesc symbol:ath9k_hw_txstart symbol:ath9k_hw_puttxbuf symbol:ath9k_hw_gettxbuf symbol:ath9k_hw_setuprxdesc symbol:ath9k_hw_setup_statusring symbol:ath9k_hw_process_rxdesc_edma symbol:ath9k_hw_addrxbuf_edma symbol:ath9k_hw_set_rx_bufsize symbol:ar9003_hw_set_paprd_txdesc symbol:ar9003_paprd_is_done symbol:ar9003_paprd_init_table symbol:ar9003_paprd_create_curve symbol:ar9003_paprd_setup_gain_table symbol:ar9003_paprd_populate_single_table symbol:ar9003_paprd_enable
ath

drivers/net/wireless/ath/ar9170/ar9170usb.ko usb:v1668p1200d*dc*dsc*dp*ic*isc*ip* usb:v057Cp8402d*dc*dsc*dp*ic*isc*ip* usb:v0409p0249d*dc*dsc*dp*ic*isc*ip* usb:v057Cp8401d*dc*dsc*dp*ic*isc*ip* usb:v04BBp093Fd*dc*dsc*dp*ic*isc*ip* usb:v2019p5304d*dc*dsc*dp*ic*isc*ip* usb:v083ApF522d*dc*dsc*dp*ic*isc*ip* usb:v0CDEp0027d*dc*dsc*dp*ic*isc*ip* usb:v0CDEp0026d*dc*dsc*dp*ic*isc*ip* usb:v0CDEp0023d*dc*dsc*dp*ic*isc*ip* usb:v0586p3417d*dc*dsc*dp*ic*isc*ip* usb:v1435p0326d*dc*dsc*dp*ic*isc*ip* usb:v1435p0804d*dc*dsc*dp*ic*isc*ip* usb:v0ACEp1221d*dc*dsc*dp*ic*isc*ip* usb:v0846p9001d*dc*dsc*dp*ic*isc*ip* usb:v0846p9010d*dc*dsc*dp*ic*isc*ip* usb:v0846p9040d*dc*dsc*dp*ic*isc*ip* usb:v07D1p3A09d*dc*dsc*dp*ic*isc*ip* usb:v07D1p3C10d*dc*dsc*dp*ic*isc*ip* usb:vCACEp0300d*dc*dsc*dp*ic*isc*ip* usb:v0CF3p1011d*dc*dsc*dp*ic*isc*ip* usb:v0CF3p1010d*dc*dsc*dp*ic*isc*ip* usb:v0CF3p1002d*dc*dsc*dp*ic*isc*ip* usb:v0CF3p1001d*dc*dsc*dp*ic*isc*ip* usb:v0CF3p9170d*dc*dsc*dp*ic*isc*ip*
mac80211 ath compat_firmware_class cfg80211

drivers/net/wireless/iwmc3200wifi/iwmc3200wifi.ko sdio:c*v0089d1408* sdio:c*v0089d1403*
compat_firmware_class cfg80211

drivers/net/wireless/rt2x00/rt2x00lib.ko symbol:rt2x00lib_remove_dev symbol:rt2x00lib_probe_dev symbol:rt2x00lib_rxdone symbol:rt2x00lib_txdone symbol:rt2x00lib_beacondone symbol:rt2x00mac_rfkill_poll symbol:rt2x00mac_conf_tx symbol:rt2x00mac_bss_info_changed symbol:rt2x00mac_get_stats symbol:rt2x00mac_set_key symbol:rt2x00mac_set_tim symbol:rt2x00mac_configure_filter symbol:rt2x00mac_config symbol:rt2x00mac_remove_interface symbol:rt2x00mac_add_interface symbol:rt2x00mac_stop symbol:rt2x00mac_start symbol:rt2x00mac_tx symbol:rt2x00queue_get_entry symbol:rt2x00queue_get_queue symbol:rt2x00queue_unmap_skb symbol:rt2x00queue_map_txskb
mac80211 compat_firmware_class cfg80211

drivers/net/wireless/rt2x00/rt73usb.ko usb:v0586p3415d*dc*dsc*dp*ic*isc*ip* usb:v0CDEp001Cd*dc*dsc*dp*ic*isc*ip* usb:v7167p3840d*dc*dsc*dp*ic*isc*ip* usb:v2019pAB50d*dc*dsc*dp*ic*isc*ip* usb:v2019pAB01d*dc*dsc*dp*ic*isc*ip* usb:v0471p200Ad*dc*dsc*dp*ic*isc*ip* usb:v6933p5001d*dc*dsc*dp*ic*isc*ip* usb:v0769p31F3d*dc*dsc*dp*ic*isc*ip* usb:v0DF6p9712d*dc*dsc*dp*ic*isc*ip* usb:v0DF6p90ACd*dc*dsc*dp*ic*isc*ip* usb:v0DF6p002Fd*dc*dsc*dp*ic*isc*ip* usb:v0DF6p0027d*dc*dsc*dp*ic*isc*ip* usb:v0DF6p0024d*dc*dsc*dp*ic*isc*ip* usb:v1740p7100d*dc*dsc*dp*ic*isc*ip* usb:v04E8p4471d*dc*dsc*dp*ic*isc*ip* usb:v18E8p6238d*dc*dsc*dp*ic*isc*ip* usb:v18E8p6229d*dc*dsc*dp*ic*isc*ip* usb:v18E8p6196d*dc*dsc*dp*ic*isc*ip* usb:v148Fp2671d*dc*dsc*dp*ic*isc*ip* usb:v148Fp2573d*dc*dsc*dp*ic*isc*ip* usb:v04BBp093Dd*dc*dsc*dp*ic*isc*ip* usb:v1B75p7318d*dc*dsc*dp*ic*isc*ip* usb:v0DB0pA874d*dc*dsc*dp*ic*isc*ip* usb:v0DB0pA861d*dc*dsc*dp*ic*isc*ip* usb:v0DB0p6874d*dc*dsc*dp*ic*isc*ip* usb:v0DB0p6877d*dc*dsc*dp*ic*isc*ip* usb:v0DB0p4600d*dc*dsc*dp*ic*isc*ip* usb:v13B1p0028d*dc*dsc*dp*ic*isc*ip* usb:v13B1p0023d*dc*dsc*dp*ic*isc*ip* usb:v13B1p0020d*dc*dsc*dp*ic*isc*ip* usb:v06F8pE020d*dc*dsc*dp*ic*isc*ip* usb:v06F8pE010d*dc*dsc*dp*ic*isc*ip* usb:v06F8pE002d*dc*dsc*dp*ic*isc*ip* usb:v1472p0009d*dc*dsc*dp*ic*isc*ip* usb:v1044p800Ad*dc*dsc*dp*ic*isc*ip* usb:v1044p8008d*dc*dsc*dp*ic*isc*ip* usb:v15A9p0004d*dc*dsc*dp*ic*isc*ip* usb:v1740p3701d*dc*dsc*dp*ic*isc*ip* usb:v7392p7618d*dc*dsc*dp*ic*isc*ip* usb:v7392p7318d*dc*dsc*dp*ic*isc*ip* usb:v07D1p3C07d*dc*dsc*dp*ic*isc*ip* usb:v07D1p3C06d*dc*dsc*dp*ic*isc*ip* usb:v07D1p3C04d*dc*dsc*dp*ic*isc*ip* usb:v07D1p3C03d*dc*dsc*dp*ic*isc*ip* usb:v07AAp002Ed*dc*dsc*dp*ic*isc*ip* usb:v14B2p3C22d*dc*dsc*dp*ic*isc*ip* usb:v1371p9032d*dc*dsc*dp*ic*isc*ip* usb:v1371p9022d*dc*dsc*dp*ic*isc*ip* usb:v178Dp02BEd*dc*dsc*dp*ic*isc*ip* usb:v0411p0119d*dc*dsc*dp*ic*isc*ip* usb:v0411p0116d*dc*dsc*dp*ic*isc*ip* usb:v0411p00F4d*dc*dsc*dp*ic*isc*ip* usb:v0411p00D9d*dc*dsc*dp*ic*isc*ip* usb:v0411p00D8d*dc*dsc*dp*ic*isc*ip* usb:v08DDp0120d*dc*dsc*dp*ic*isc*ip* usb:v1631pC019d*dc*dsc*dp*ic*isc*ip* usb:v050Dp905Cd*dc*dsc*dp*ic*isc*ip* usb:v050Dp905Bd*dc*dsc*dp*ic*isc*ip* usb:v050Dp705Ad*dc*dsc*dp*ic*isc*ip* usb:v050Dp7050d*dc*dsc*dp*ic*isc*ip* usb:v0B05p1724d*dc*dsc*dp*ic*isc*ip* usb:v0B05p1723d*dc*dsc*dp*ic*isc*ip* usb:v1690p0722d*dc*dsc*dp*ic*isc*ip* usb:v18C5p0002d*dc*dsc*dp*ic*isc*ip* usb:v0EB0p9021d*dc*dsc*dp*ic*isc*ip* usb:v148Fp9021d*dc*dsc*dp*ic*isc*ip* usb:v14B2p3C10d*dc*dsc*dp*ic*isc*ip* usb:v07B8pB21Fd*dc*dsc*dp*ic*isc*ip* usb:v07B8pB21Ed*dc*dsc*dp*ic*isc*ip* usb:v07B8pB21Dd*dc*dsc*dp*ic*isc*ip* usb:v07B8pB21Cd*dc*dsc*dp*ic*isc*ip* usb:v07B8pB21Bd*dc*dsc*dp*ic*isc*ip*
rt2x00usb rt2x00lib

drivers/net/wireless/rt2x00/rt2800usb.ko usb:v0586p341Ad*dc*dsc*dp*ic*isc*ip* usb:v177Fp0313d*dc*dsc*dp*ic*isc*ip* usb:v177Fp0153d*dc*dsc*dp*ic*isc*ip* usb:v083ApF511d*dc*dsc*dp*ic*isc*ip* usb:v083ApD522d*dc*dsc*dp*ic*isc*ip* usb:v083ApC522d*dc*dsc*dp*ic*isc*ip* usb:v083ApA512d*dc*dsc*dp*ic*isc*ip* usb:v18E8p6259d*dc*dsc*dp*ic*isc*ip* usb:v2019pAB24d*dc*dsc*dp*ic*isc*ip* usb:v1D4Dp0011d*dc*dsc*dp*ic*isc*ip* usb:v1D4Dp0010d*dc*dsc*dp*ic*isc*ip* usb:v1D4Dp0002d*dc*dsc*dp*ic*isc*ip* usb:v05A6p0101d*dc*dsc*dp*ic*isc*ip* usb:v1B75p3072d*dc*dsc*dp*ic*isc*ip* usb:v1B75p3071d*dc*dsc*dp*ic*isc*ip* usb:v100Dp9032d*dc*dsc*dp*ic*isc*ip* usb:v1737p0079d*dc*dsc*dp*ic*isc*ip* usb:v1737p0078d*dc*dsc*dp*ic*isc*ip* usb:v1737p0077d*dc*dsc*dp*ic*isc*ip* usb:v1740p0615d*dc*dsc*dp*ic*isc*ip* usb:v1740p0605d*dc*dsc*dp*ic*isc*ip* usb:v1044p800Cd*dc*dsc*dp*ic*isc*ip* usb:v15A9p0010d*dc*dsc*dp*ic*isc*ip* usb:v203Dp14A1d*dc*dsc*dp*ic*isc*ip* usb:v07D1p3C17d*dc*dsc*dp*ic*isc*ip* usb:v07D1p3C15d*dc*dsc*dp*ic*isc*ip* usb:v07D1p3C13d*dc*dsc*dp*ic*isc*ip* usb:v07D1p3C0Bd*dc*dsc*dp*ic*isc*ip* usb:v18C5p0008d*dc*dsc*dp*ic*isc*ip* usb:v07AAp0042d*dc*dsc*dp*ic*isc*ip* usb:v07AAp0041d*dc*dsc*dp*ic*isc*ip* usb:v14B2p3C11d*dc*dsc*dp*ic*isc*ip* usb:v14B2p3C08d*dc*dsc*dp*ic*isc*ip* usb:v0411p015Dd*dc*dsc*dp*ic*isc*ip* usb:v0411p0150d*dc*dsc*dp*ic*isc*ip* usb:v0411p0148d*dc*dsc*dp*ic*isc*ip* usb:v0411p012Ed*dc*dsc*dp*ic*isc*ip* usb:v050Dp825Ad*dc*dsc*dp*ic*isc*ip* usb:v13D3p3322d*dc*dsc*dp*ic*isc*ip* usb:v13D3p3284d*dc*dsc*dp*ic*isc*ip* usb:v13D3p3262d*dc*dsc*dp*ic*isc*ip* usb:v1761p0B05d*dc*dsc*dp*ic*isc*ip* usb:v0B05p1790d*dc*dsc*dp*ic*isc*ip* usb:v0B05p1761d*dc*dsc*dp*ic*isc*ip* usb:v0B05p1760d*dc*dsc*dp*ic*isc*ip* usb:v0E0Bp9041d*dc*dsc*dp*ic*isc*ip* usb:v0E0Bp9031d*dc*dsc*dp*ic*isc*ip* usb:v5A57p0284d*dc*dsc*dp*ic*isc*ip* usb:v0DF6p0050d*dc*dsc*dp*ic*isc*ip* usb:v0DF6p0041d*dc*dsc*dp*ic*isc*ip* usb:v148Fp8070d*dc*dsc*dp*ic*isc*ip* usb:v148Fp3572d*dc*dsc*dp*ic*isc*ip* usb:v148Fp3370d*dc*dsc*dp*ic*isc*ip* usb:v04BBp0944d*dc*dsc*dp*ic*isc*ip* usb:v1740p9801d*dc*dsc*dp*ic*isc*ip* usb:v167Bp4001d*dc*dsc*dp*ic*isc*ip* usb:v1690p0744d*dc*dsc*dp*ic*isc*ip* usb:v8516p3572d*dc*dsc*dp*ic*isc*ip* usb:v5A57p5257d*dc*dsc*dp*ic*isc*ip* usb:v5A57p0283d*dc*dsc*dp*ic*isc*ip* usb:v083ApA703d*dc*dsc*dp*ic*isc*ip* usb:v083ApA702d*dc*dsc*dp*ic*isc*ip* usb:v083ApA701d*dc*dsc*dp*ic*isc*ip* usb:v083Ap7511d*dc*dsc*dp*ic*isc*ip* usb:v0DF6p0048d*dc*dsc*dp*ic*isc*ip* usb:v0DF6p0047d*dc*dsc*dp*ic*isc*ip* usb:v0DF6p0042d*dc*dsc*dp*ic*isc*ip* usb:v0DF6p0040d*dc*dsc*dp*ic*isc*ip* usb:v0DF6p003Ed*dc*dsc*dp*ic*isc*ip* usb:v148Fp3072d*dc*dsc*dp*ic*isc*ip* usb:v148Fp3071d*dc*dsc*dp*ic*isc*ip* usb:v148Fp3070d*dc*dsc*dp*ic*isc*ip* usb:v148Fp2070d*dc*dsc*dp*ic*isc*ip* usb:v1A32p0304d*dc*dsc*dp*ic*isc*ip* usb:v2019pAB25d*dc*dsc*dp*ic*isc*ip* usb:v1D4Dp000Ed*dc*dsc*dp*ic*isc*ip* usb:v1D4Dp000Cd*dc*dsc*dp*ic*isc*ip* usb:v20B8p8888d*dc*dsc*dp*ic*isc*ip* usb:v0DB0p899Ad*dc*dsc*dp*ic*isc*ip* usb:v0DB0p871Cd*dc*dsc*dp*ic*isc*ip* usb:v0DB0p871Bd*dc*dsc*dp*ic*isc*ip* usb:v0DB0p871Ad*dc*dsc*dp*ic*isc*ip* usb:v0DB0p870Ad*dc*dsc*dp*ic*isc*ip* usb:v0DB0p822Cd*dc*dsc*dp*ic*isc*ip* usb:v0DB0p822Bd*dc*dsc*dp*ic*isc*ip* usb:v0DB0p822Ad*dc*dsc*dp*ic*isc*ip* usb:v0DB0p821Ad*dc*dsc*dp*ic*isc*ip* usb:v0DB0p3871d*dc*dsc*dp*ic*isc*ip* usb:v0DB0p3870d*dc*dsc*dp*ic*isc*ip* usb:v0DB0p3822d*dc*dsc*dp*ic*isc*ip* usb:v0DB0p3821d*dc*dsc*dp*ic*isc*ip* usb:v0DB0p3820d*dc*dsc*dp*ic*isc*ip* usb:v0789p0166d*dc*dsc*dp*ic*isc*ip* usb:v04BBp0948d*dc*dsc*dp*ic*isc*ip* usb:v04BBp0947d*dc*dsc*dp*ic*isc*ip* usb:v04BBp0945d*dc*dsc*dp*ic*isc*ip* usb:v1044p800Dd*dc*dsc*dp*ic*isc*ip* usb:v1740p9709d*dc*dsc*dp*ic*isc*ip* usb:v1740p9708d*dc*dsc*dp*ic*isc*ip* usb:v1740p9707d*dc*dsc*dp*ic*isc*ip* usb:v1740p9706d*dc*dsc*dp*ic*isc*ip* usb:v1740p9705d*dc*dsc*dp*ic*isc*ip* usb:v1740p9703d*dc*dsc*dp*ic*isc*ip* usb:v203Dp14A9d*dc*dsc*dp*ic*isc*ip* usb:v203Dp1480d*dc*dsc*dp*ic*isc*ip* usb:v7392p7711d*dc*dsc*dp*ic*isc*ip* usb:v07FAp7712d*dc*dsc*dp*ic*isc*ip* usb:v07D1p3C16d*dc*dsc*dp*ic*isc*ip* usb:v07D1p3C0Fd*dc*dsc*dp*ic*isc*ip* usb:v07D1p3C0Ed*dc*dsc*dp*ic*isc*ip* usb:v07D1p3C0Dd*dc*dsc*dp*ic*isc*ip* usb:v07D1p3C0Ad*dc*dsc*dp*ic*isc*ip* usb:v18C5p0012d*dc*dsc*dp*ic*isc*ip* usb:v14B2p3C12d*dc*dsc*dp*ic*isc*ip* usb:v13D3p3321d*dc*dsc*dp*ic*isc*ip* usb:v13D3p3307d*dc*dsc*dp*ic*isc*ip* usb:v13D3p3305d*dc*dsc*dp*ic*isc*ip* usb:v13D3p3273d*dc*dsc*dp*ic*isc*ip* usb:v0B05p1784d*dc*dsc*dp*ic*isc*ip* usb:v8516p3072d*dc*dsc*dp*ic*isc*ip* usb:v8516p3071d*dc*dsc*dp*ic*isc*ip* usb:v8516p3070d*dc*dsc*dp*ic*isc*ip* usb:v1EDAp2310d*dc*dsc*dp*ic*isc*ip* usb:v07B8p3072d*dc*dsc*dp*ic*isc*ip* usb:v07B8p3071d*dc*dsc*dp*ic*isc*ip* usb:v07B8p3070d*dc*dsc*dp*ic*isc*ip* usb:v0586p3416d*dc*dsc*dp*ic*isc*ip* usb:v5A57p0282d*dc*dsc*dp*ic*isc*ip* usb:v5A57p0280d*dc*dsc*dp*ic*isc*ip* usb:v0CDEp0025d*dc*dsc*dp*ic*isc*ip* usb:v0CDEp0022d*dc*dsc*dp*ic*isc*ip* usb:v157Ep300Ed*dc*dsc*dp*ic*isc*ip* usb:v177Fp0302d*dc*dsc*dp*ic*isc*ip* usb:v15A9p0006d*dc*dsc*dp*ic*isc*ip* usb:v083ApB522d*dc*dsc*dp*ic*isc*ip* usb:v083ApA618d*dc*dsc*dp*ic*isc*ip* usb:v083Ap8522d*dc*dsc*dp*ic*isc*ip* usb:v083Ap7522d*dc*dsc*dp*ic*isc*ip* usb:v083Ap7512d*dc*dsc*dp*ic*isc*ip* usb:v083Ap6618d*dc*dsc*dp*ic*isc*ip* usb:v0DF6p003Fd*dc*dsc*dp*ic*isc*ip* usb:v0DF6p003Dd*dc*dsc*dp*ic*isc*ip* usb:v0DF6p003Bd*dc*dsc*dp*ic*isc*ip* usb:v0DF6p0039d*dc*dsc*dp*ic*isc*ip* usb:v0DF6p002Dd*dc*dsc*dp*ic*isc*ip* usb:v0DF6p002Cd*dc*dsc*dp*ic*isc*ip* usb:v0DF6p002Bd*dc*dsc*dp*ic*isc*ip* usb:v0DF6p0017d*dc*dsc*dp*ic*isc*ip* usb:v129Bp1828d*dc*dsc*dp*ic*isc*ip* usb:v04E8p2018d*dc*dsc*dp*ic*isc*ip* usb:v148Fp2870d*dc*dsc*dp*ic*isc*ip* usb:v148Fp2770d*dc*dsc*dp*ic*isc*ip* usb:v2019pED06d*dc*dsc*dp*ic*isc*ip* usb:v0471p200Fd*dc*dsc*dp*ic*isc*ip* usb:v0DB0p6899d*dc*dsc*dp*ic*isc*ip* usb:v100Dp9031d*dc*dsc*dp*ic*isc*ip* usb:v0789p0164d*dc*dsc*dp*ic*isc*ip* usb:v0789p0163d*dc*dsc*dp*ic*isc*ip* usb:v0789p0162d*dc*dsc*dp*ic*isc*ip* usb:v1737p0071d*dc*dsc*dp*ic*isc*ip* usb:v1737p0070d*dc*dsc*dp*ic*isc*ip* usb:v0E66p0018d*dc*dsc*dp*ic*isc*ip* usb:v0E66p0017d*dc*dsc*dp*ic*isc*ip* usb:v0E66p0013d*dc*dsc*dp*ic*isc*ip* usb:v0E66p000Bd*dc*dsc*dp*ic*isc*ip* usb:v0E66p0009d*dc*dsc*dp*ic*isc*ip* usb:v0E66p0003d*dc*dsc*dp*ic*isc*ip* usb:v0E66p0001d*dc*dsc*dp*ic*isc*ip* usb:v1044p800Bd*dc*dsc*dp*ic*isc*ip* usb:v1740p9702d*dc*dsc*dp*ic*isc*ip* usb:v1740p9701d*dc*dsc*dp*ic*isc*ip* usb:v7392p7718d*dc*dsc*dp*ic*isc*ip* usb:v7392p7717d*dc*dsc*dp*ic*isc*ip* usb:v07D1p3C11d*dc*dsc*dp*ic*isc*ip* usb:v07D1p3C09d*dc*dsc*dp*ic*isc*ip* usb:v07AAp003Fd*dc*dsc*dp*ic*isc*ip* usb:v07AAp003Cd*dc*dsc*dp*ic*isc*ip* usb:v07AAp002Fd*dc*dsc*dp*ic*isc*ip* usb:v14B2p3C28d*dc*dsc*dp*ic*isc*ip* usb:v14B2p3C27d*dc*dsc*dp*ic*isc*ip* usb:v14B2p3C25d*dc*dsc*dp*ic*isc*ip* usb:v14B2p3C23d*dc*dsc*dp*ic*isc*ip* usb:v14B2p3C09d*dc*dsc*dp*ic*isc*ip* usb:v14B2p3C07d*dc*dsc*dp*ic*isc*ip* usb:v14B2p3C06d*dc*dsc*dp*ic*isc*ip* usb:v0411p00E8d*dc*dsc*dp*ic*isc*ip* usb:v050Dp815Cd*dc*dsc*dp*ic*isc*ip* usb:v050Dp805Cd*dc*dsc*dp*ic*isc*ip* usb:v050Dp8053d*dc*dsc*dp*ic*isc*ip* usb:v13D3p3247d*dc*dsc*dp*ic*isc*ip* usb:v0B05p1742d*dc*dsc*dp*ic*isc*ip* usb:v0B05p1732d*dc*dsc*dp*ic*isc*ip* usb:v0B05p1731d*dc*dsc*dp*ic*isc*ip* usb:v1690p0740d*dc*dsc*dp*ic*isc*ip* usb:v15C5p0008d*dc*dsc*dp*ic*isc*ip* usb:v8516p2870d*dc*dsc*dp*ic*isc*ip* usb:v8516p2770d*dc*dsc*dp*ic*isc*ip* usb:v8516p2070d*dc*dsc*dp*ic*isc*ip* usb:v1482p3C09d*dc*dsc*dp*ic*isc*ip* usb:v07B8p2770d*dc*dsc*dp*ic*isc*ip* usb:v07B8p2870d*dc*dsc*dp*ic*isc*ip*
rt2x00usb rt2800lib

drivers/net/wireless/rt2x00/rt2500usb.ko usb:v5A57p0260d*dc*dsc*dp*ic*isc*ip* usb:v0F88p3012d*dc*dsc*dp*ic*isc*ip* usb:v0EB0p9020d*dc*dsc*dp*ic*isc*ip* usb:v0769p11F3d*dc*dsc*dp*ic*isc*ip* usb:v114Bp0110d*dc*dsc*dp*ic*isc*ip* usb:v0707pEE13d*dc*dsc*dp*ic*isc*ip* usb:v0681p3C06d*dc*dsc*dp*ic*isc*ip* usb:v079Bp004Bd*dc*dsc*dp*ic*isc*ip* usb:v148Fp9020d*dc*dsc*dp*ic*isc*ip* usb:v148Fp2573d*dc*dsc*dp*ic*isc*ip* usb:v148Fp2570d*dc*dsc*dp*ic*isc*ip* usb:v148Fp1706d*dc*dsc*dp*ic*isc*ip* usb:v0DB0p6869d*dc*dsc*dp*ic*isc*ip* usb:v0DB0p6865d*dc*dsc*dp*ic*isc*ip* usb:v0DB0p6861d*dc*dsc*dp*ic*isc*ip* usb:v0411p0097d*dc*dsc*dp*ic*isc*ip* usb:v0411p008Bd*dc*dsc*dp*ic*isc*ip* usb:v0411p0067d*dc*dsc*dp*ic*isc*ip* usb:v0411p0066d*dc*dsc*dp*ic*isc*ip* usb:v0411p005Ed*dc*dsc*dp*ic*isc*ip* usb:v06F8pE000d*dc*dsc*dp*ic*isc*ip* usb:v1044p8007d*dc*dsc*dp*ic*isc*ip* usb:v1044p8001d*dc*dsc*dp*ic*isc*ip* usb:v2001p3C00d*dc*dsc*dp*ic*isc*ip* usb:v14B2p3C02d*dc*dsc*dp*ic*isc*ip* usb:v1371p9022d*dc*dsc*dp*ic*isc*ip* usb:v13B1p001Ad*dc*dsc*dp*ic*isc*ip* usb:v13B1p0011d*dc*dsc*dp*ic*isc*ip* usb:v13B1p000Dd*dc*dsc*dp*ic*isc*ip* usb:v050Dp705Ad*dc*dsc*dp*ic*isc*ip* usb:v050Dp7051d*dc*dsc*dp*ic*isc*ip* usb:v050Dp7050d*dc*dsc*dp*ic*isc*ip* usb:v0B05p1707d*dc*dsc*dp*ic*isc*ip* usb:v0B05p1706d*dc*dsc*dp*ic*isc*ip*
rt2x00usb rt2x00lib

drivers/net/wireless/rt2x00/rt2800lib.ko symbol:rt2800_write_beacon symbol:rt2800_mac80211_ops symbol:rt2800_probe_hw_mode symbol:rt2800_init_eeprom symbol:rt2800_validate_eeprom symbol:rt2800_read_eeprom_efuse symbol:rt2800_efuse_detect symbol:rt2800_init_rfcsr symbol:rt2800_init_bbp symbol:rt2800_init_registers symbol:rt2800_link_tuner symbol:rt2800_reset_tuner symbol:rt2800_link_stats symbol:rt2800_config symbol:rt2800_config_ant symbol:rt2800_config_erp symbol:rt2800_config_intf symbol:rt2800_config_filter symbol:rt2800_config_pairwise_key symbol:rt2800_config_shared_key symbol:rt2800_rfkill_poll symbol:rt2800_process_rxwi symbol:rt2800_write_txwi symbol:rt2800_wait_wpdma_ready symbol:rt2800_mcu_request
rt2x00lib

drivers/net/wireless/rt2x00/rt2x00usb.ko symbol:rt2x00usb_disconnect symbol:rt2x00usb_probe symbol:rt2x00usb_uninitialize symbol:rt2x00usb_initialize symbol:rt2x00usb_clear_entry symbol:rt2x00usb_disable_radio symbol:rt2x00usb_kill_tx_queue symbol:rt2x00usb_kick_tx_queue symbol:rt2x00usb_write_tx_data symbol:rt2x00usb_regbusy_read symbol:rt2x00usb_vendor_request_buff symbol:rt2x00usb_vendor_req_buff_lock symbol:rt2x00usb_vendor_request
rt2x00lib mac80211

drivers/net/wireless/wl12xx/wl1251_sdio.ko sdio:c*v104Cd9066*
mac80211 wl1251

drivers/net/wireless/wl12xx/wl1271_sdio.ko sdio:c*v0097d4076*
mac80211

drivers/net/wireless/wl12xx/wl1251.ko spi:wl1251 symbol:wl1251_free_hw symbol:wl1251_alloc_hw symbol:wl1251_init_ieee80211
compat_firmware_class mac80211 cfg80211

drivers/net/wireless/libertas_tf/libertas_tf.ko symbol:lbtf_bcn_sent symbol:lbtf_send_tx_feedback symbol:lbtf_remove_card symbol:lbtf_add_card symbol:lbtf_rx symbol:lbtf_debug symbol:lbtf_cmd_response_rx symbol:__lbtf_cmd symbol:lbtf_cmd_copyback
mac80211

drivers/net/wireless/libertas_tf/libertas_tf_usb.ko usb:v05A3p8388d*dc*dsc*dp*ic*isc*ip* usb:v1286p2001d*dc*dsc*dp*ic*isc*ip* symbol:if_usb_prog_firmware symbol:if_usb_reset_device
compat_firmware_class libertas_tf

drivers/net/wireless/p54/p54usb.ko prism54usb usb:v413Cp8104d*dc*dsc*dp*ic*isc*ip* usb:v413Cp8102d*dc*dsc*dp*ic*isc*ip* usb:v413Cp5513d*dc*dsc*dp*ic*isc*ip* usb:v2001p3704d*dc*dsc*dp*ic*isc*ip* usb:v1435p0427d*dc*dsc*dp*ic*isc*ip* usb:v1413p5400d*dc*dsc*dp*ic*isc*ip* usb:v13B1p000Cd*dc*dsc*dp*ic*isc*ip* usb:v13B1p000Ad*dc*dsc*dp*ic*isc*ip* usb:v1260pEE22d*dc*dsc*dp*ic*isc*ip* usb:v124Ap4025d*dc*dsc*dp*ic*isc*ip* usb:v0D8Ep3762d*dc*dsc*dp*ic*isc*ip* usb:v0CDEp0015d*dc*dsc*dp*ic*isc*ip* usb:v0CDEp0008d*dc*dsc*dp*ic*isc*ip* usb:v0BF8p1009d*dc*dsc*dp*ic*isc*ip* usb:v0BAFp0118d*dc*dsc*dp*ic*isc*ip* usb:v0915p2002d*dc*dsc*dp*ic*isc*ip* usb:v0915p2000d*dc*dsc*dp*ic*isc*ip* usb:v0846p4240d*dc*dsc*dp*ic*isc*ip* usb:v083ApF503d*dc*dsc*dp*ic*isc*ip* usb:v083Ap4521d*dc*dsc*dp*ic*isc*ip* usb:v0707pEE13d*dc*dsc*dp*ic*isc*ip* usb:v06B9p0121d*dc*dsc*dp*ic*isc*ip* usb:v0572p2002d*dc*dsc*dp*ic*isc*ip* usb:v0572p2000d*dc*dsc*dp*ic*isc*ip* usb:v050Dp7050d*dc*dsc*dp*ic*isc*ip* usb:v0471p1230d*dc*dsc*dp*ic*isc*ip* usb:v5041p2235d*dc*dsc*dp*ic*isc*ip* usb:v5041p2234d*dc*dsc*dp*ic*isc*ip* usb:v2001p3703d*dc*dsc*dp*ic*isc*ip* usb:v2001p3701d*dc*dsc*dp*ic*isc*ip* usb:v1915p2235d*dc*dsc*dp*ic*isc*ip* usb:v1915p2234d*dc*dsc*dp*ic*isc*ip* usb:v124Ap4023d*dc*dsc*dp*ic*isc*ip* usb:v0CDEp0006d*dc*dsc*dp*ic*isc*ip* usb:v09AAp1000d*dc*dsc*dp*ic*isc*ip* usb:v0846p4220d*dc*dsc*dp*ic*isc*ip* usb:v0846p4210d*dc*dsc*dp*ic*isc*ip* usb:v0846p4200d*dc*dsc*dp*ic*isc*ip* usb:v083Ap5501d*dc*dsc*dp*ic*isc*ip* usb:v083Ap4502d*dc*dsc*dp*ic*isc*ip* usb:v083Ap4501d*dc*dsc*dp*ic*isc*ip* usb:v07AAp001Cd*dc*dsc*dp*ic*isc*ip* usb:v0707pEE06d*dc*dsc*dp*ic*isc*ip* usb:v06B9p0120d*dc*dsc*dp*ic*isc*ip* usb:v0506p0A11d*dc*dsc*dp*ic*isc*ip*
p54common compat_firmware_class mac80211

drivers/net/wireless/p54/p54common.ko prism54common symbol:p54_read_eeprom symbol:p54_parse_eeprom symbol:p54_parse_firmware symbol:p54_rx symbol:p54_free_skb symbol:p54_unregister_common symbol:p54_free_common symbol:p54_register_common symbol:p54_init_common
mac80211 cfg80211

drivers/net/wireless/zd1211rw/zd1211rw.ko usb:v0ACEp20FFd*dc*dsc*dp*ic*isc*ip* usb:v0ACEp2011d*dc*dsc*dp*ic*isc*ip* usb:v2019p5303d*dc*dsc*dp*ic*isc*ip* usb:v1582p6003d*dc*dsc*dp*ic*isc*ip* usb:v157Ep300Dd*dc*dsc*dp*ic*isc*ip* usb:v13B1p0024d*dc*dsc*dp*ic*isc*ip* usb:v129Bp1667d*dc*dsc*dp*ic*isc*ip* usb:v0DF6p0036d*dc*dsc*dp*ic*isc*ip* usb:v0CDEp001Ad*dc*dsc*dp*ic*isc*ip* usb:v0BAFp0121d*dc*dsc*dp*ic*isc*ip* usb:v0B05p171Bd*dc*dsc*dp*ic*isc*ip* usb:v0ACEpB215d*dc*dsc*dp*ic*isc*ip* usb:v0ACEp1215d*dc*dsc*dp*ic*isc*ip* usb:v083ApE506d*dc*dsc*dp*ic*isc*ip* usb:v083ApE503d*dc*dsc*dp*ic*isc*ip* usb:v083ApE501d*dc*dsc*dp*ic*isc*ip* usb:v083Ap4505d*dc*dsc*dp*ic*isc*ip* usb:v07FAp1196d*dc*dsc*dp*ic*isc*ip* usb:v07B8p6001d*dc*dsc*dp*ic*isc*ip* usb:v079Bp0062d*dc*dsc*dp*ic*isc*ip* usb:v0586p3413d*dc*dsc*dp*ic*isc*ip* usb:v0586p3412d*dc*dsc*dp*ic*isc*ip* usb:v0586p3410d*dc*dsc*dp*ic*isc*ip* usb:v0586p340Fd*dc*dsc*dp*ic*isc*ip* usb:v0586p340Ad*dc*dsc*dp*ic*isc*ip* usb:v054Cp0257d*dc*dsc*dp*ic*isc*ip* usb:v050Dp705Cd*dc*dsc*dp*ic*isc*ip* usb:v0471p1237d*dc*dsc*dp*ic*isc*ip* usb:v0471p1236d*dc*dsc*dp*ic*isc*ip* usb:v0411p00DAd*dc*dsc*dp*ic*isc*ip* usb:v0409p0248d*dc*dsc*dp*ic*isc*ip* usb:v0053p5301d*dc*dsc*dp*ic*isc*ip* usb:v6891pA727d*dc*dsc*dp*ic*isc*ip* usb:v1740p2000d*dc*dsc*dp*ic*isc*ip* usb:v157Ep3204d*dc*dsc*dp*ic*isc*ip* usb:v157Ep300Bd*dc*dsc*dp*ic*isc*ip* usb:v157Ep300Ad*dc*dsc*dp*ic*isc*ip* usb:v14EApAB13d*dc*dsc*dp*ic*isc*ip* usb:v1435p0711d*dc*dsc*dp*ic*isc*ip* usb:v13B1p001Ed*dc*dsc*dp*ic*isc*ip* usb:v129Bp1666d*dc*dsc*dp*ic*isc*ip* usb:v126FpA006d*dc*dsc*dp*ic*isc*ip* usb:v0DF6p9075d*dc*dsc*dp*ic*isc*ip* usb:v0DF6p9071d*dc*dsc*dp*ic*isc*ip* usb:v0B3Bp5630d*dc*dsc*dp*ic*isc*ip* usb:v0B3Bp1630d*dc*dsc*dp*ic*isc*ip* usb:v0B05p170Cd*dc*dsc*dp*ic*isc*ip* usb:v0ACEpA211d*dc*dsc*dp*ic*isc*ip* usb:v0ACEp1211d*dc*dsc*dp*ic*isc*ip* usb:v07B8p6001d*dc*dsc*dp*ic*isc*ip* usb:v079Bp004Ad*dc*dsc*dp*ic*isc*ip* usb:v0586p3409d*dc*dsc*dp*ic*isc*ip* usb:v0586p3407d*dc*dsc*dp*ic*isc*ip* usb:v0586p3402d*dc*dsc*dp*ic*isc*ip* usb:v0586p3401d*dc*dsc*dp*ic*isc*ip* usb:v0105p145Fd*dc*dsc*dp*ic*isc*ip*
mac80211 compat_firmware_class cfg80211

drivers/net/wireless/rndis_wlan.ko usb:v*p*d*dc*dsc*dp*icEFisc01ip01* usb:v*p*d*dc*dsc*dp*ic02isc02ipFF* usb:v0411p004Bd*dc*dsc*dp*ic02isc02ipFF* usb:v0BAFp0111d*dc*dsc*dp*ic02isc02ipFF* usb:v13B1p000Ed*dc*dsc*dp*ic02isc02ipFF* usb:v1690p0715d*dc*dsc*dp*ic02isc02ipFF* usb:v0A5CpD11Bd*dc*dsc*dp*ic02isc02ipFF* usb:v0B05p1717d*dc*dsc*dp*ic02isc02ipFF* usb:v13B1p0026d*dc*dsc*dp*ic02isc02ipFF* usb:v13B1p0014d*dc*dsc*dp*ic02isc02ipFF* usb:v1799p011Bd*dc*dsc*dp*ic02isc02ipFF* usb:v050Dp011Bd*dc*dsc*dp*ic02isc02ipFF* usb:v0BAFp011Bd*dc*dsc*dp*ic02isc02ipFF* usb:v0411p00BCd*dc*dsc*dp*ic02isc02ipFF*
usbnet rndis_host cfg80211

drivers/net/usb/rndis_host.ko usb:v*p*d*dc*dsc*dp*icE0isc01ip03* usb:v*p*d*dc*dsc*dp*icEFisc01ip01* usb:v*p*d*dc*dsc*dp*ic02isc02ipFF* symbol:rndis_tx_fixup symbol:rndis_rx_fixup symbol:rndis_unbind symbol:generic_rndis_bind symbol:rndis_command symbol:rndis_status
usbnet cdc_ether

drivers/net/usb/usbnet.ko symbol:usbnet_resume symbol:usbnet_suspend symbol:usbnet_probe symbol:usbnet_disconnect symbol:usbnet_start_xmit symbol:usbnet_tx_timeout symbol:usbnet_set_msglevel symbol:usbnet_get_msglevel symbol:usbnet_get_drvinfo symbol:usbnet_nway_reset symbol:usbnet_get_link symbol:usbnet_set_settings symbol:usbnet_get_settings symbol:usbnet_open symbol:usbnet_stop symbol:usbnet_unlink_rx_urbs symbol:usbnet_purge_paused_rxq symbol:usbnet_resume_rx symbol:usbnet_pause_rx symbol:usbnet_defer_kevent symbol:usbnet_change_mtu symbol:usbnet_skb_return symbol:usbnet_get_ethernet_addr symbol:usbnet_get_endpoints

drivers/net/usb/cdc_ether.ko usb:v*p*d*dc*dsc*dp*ic02isc0Aip00* usb:v*p*d*dc*dsc*dp*ic02isc06ip00* usb:v07B4p0F02d*dc*dsc*dp*ic02isc06ip00* usb:v04DDp9050d*dc*dsc*dp*ic02isc06ip00* usb:v04DDp9032d*dc*dsc*dp*ic02isc06ip00* usb:v04DDp9031d*dc*dsc*dp*ic02isc06ip00* usb:v04DDp8007d*dc*dsc*dp*ic02isc06ip00* usb:v04DDp8006d*dc*dsc*dp*ic02isc06ip00* usb:v04DDp8005d*dc*dsc*dp*ic02isc06ip00* usb:v04DDp8004d*dc*dsc*dp*ic02isc06ip00* symbol:usbnet_cdc_unbind symbol:usbnet_generic_cdc_bind
usbnet

drivers/misc/eeprom/eeprom_93cx6.ko symbol:eeprom_93cx6_multiread symbol:eeprom_93cx6_read

drivers/bluetooth/ath3k.ko usb:v0CF3p3000d*dc*dsc*dp*ic*isc*ip*
compat_firmware_class
