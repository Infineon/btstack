var group__sdp__types =
[
    [ "wiced_bt_sdp_discovery_attribute_value_t", "structwiced__bt__sdp__discovery__attribute__value__t.html", [
      [ "u8", "structwiced__bt__sdp__discovery__attribute__value__t.html#ace0e0a04c815d89277cccf143c01b77c", null ],
      [ "u16", "structwiced__bt__sdp__discovery__attribute__value__t.html#a4d57e1798e153600454a77872401f3d0", null ],
      [ "u32", "structwiced__bt__sdp__discovery__attribute__value__t.html#a4539a63e674db9a7f8679e96899c8ff6", null ],
      [ "array", "structwiced__bt__sdp__discovery__attribute__value__t.html#af6a3f4b4c91e082726806b53552a07ab", null ],
      [ "p_sub_attr", "structwiced__bt__sdp__discovery__attribute__value__t.html#a2f227b7c2507e15f733a6b84c2538e0e", null ],
      [ "v", "structwiced__bt__sdp__discovery__attribute__value__t.html#ae0b1729d1e111bfa7ece14f9e8f42e31", null ]
    ] ],
    [ "wiced_bt_sdp_discovery_attribute_t", "structwiced__bt__sdp__discovery__attribute__t.html", [
      [ "p_next_attr", "structwiced__bt__sdp__discovery__attribute__t.html#a8928cd1e5271eea889abcf0d56b99e56", null ],
      [ "attr_id", "structwiced__bt__sdp__discovery__attribute__t.html#a7607974079edbe8c3b3eca493422cf75", null ],
      [ "attr_len_type", "structwiced__bt__sdp__discovery__attribute__t.html#a1e5c9ec8233d82311ec3263cb6b0754f", null ],
      [ "attr_value", "structwiced__bt__sdp__discovery__attribute__t.html#ac8ab2352d0698804982a3ee84a110f21", null ]
    ] ],
    [ "wiced_bt_sdp_discovery_record_t", "structwiced__bt__sdp__discovery__record__t.html", [
      [ "p_first_attr", "structwiced__bt__sdp__discovery__record__t.html#a2c03131b6854412677af9229105e21fc", null ],
      [ "p_next_rec", "structwiced__bt__sdp__discovery__record__t.html#a9092f93ec78136b00a77a7d4427a7ce8", null ],
      [ "time_read", "structwiced__bt__sdp__discovery__record__t.html#acf2163c1a64b9119939ac9df95067641", null ]
    ] ],
    [ "wiced_bt_sdp_discovery_db_t", "structwiced__bt__sdp__discovery__db__t.html", [
      [ "mem_size", "structwiced__bt__sdp__discovery__db__t.html#a81d7ef3616ec429b4a18e5b9d36ac48f", null ],
      [ "mem_free", "structwiced__bt__sdp__discovery__db__t.html#a46b1feac5e72fb9e386b9df692339b06", null ],
      [ "p_first_rec", "structwiced__bt__sdp__discovery__db__t.html#a5756e0f4a5aa37bed48af0338f12512b", null ],
      [ "num_uuid_filters", "structwiced__bt__sdp__discovery__db__t.html#afe0c35dff37a42c46bd796009c2f6c74", null ],
      [ "uid_filters", "structwiced__bt__sdp__discovery__db__t.html#a466ec3bda86940a09c907ff4ca172c66", null ],
      [ "num_attr_filters", "structwiced__bt__sdp__discovery__db__t.html#a9f8b2a803f1a273cbbcd7ed70b4101bc", null ],
      [ "attr_filters", "structwiced__bt__sdp__discovery__db__t.html#a4ad626b969526631976a640932ec5bab", null ],
      [ "p_free_mem", "structwiced__bt__sdp__discovery__db__t.html#aae66b88fe1874d2c12ea4f8dc7cfacfc", null ]
    ] ],
    [ "wiced_bt_sdp_protocol_elem_t", "structwiced__bt__sdp__protocol__elem__t.html", [
      [ "protocol_uuid", "structwiced__bt__sdp__protocol__elem__t.html#ab2b2c3d1b12467aeb8e082218b584d8f", null ],
      [ "num_params", "structwiced__bt__sdp__protocol__elem__t.html#ab3aff73ba15eece3f9555b52b08a8742", null ],
      [ "params", "structwiced__bt__sdp__protocol__elem__t.html#ae2b1eeddf4a8e35b349a6ce2530fddb1", null ]
    ] ],
    [ "wiced_bt_sdp_discovery_complete_cback_t", "group__sdp__types.html#ga67cbc8e056216dc0f23717a556437565", null ],
    [ "wiced_bt_sdp_result_t", "group__sdp__types.html#ga93c6f8c9d0b76ab42e67a9f2d0dec328", [
      [ "WICED_BT_SDP_SUCCESS", "group__sdp__types.html#gga93c6f8c9d0b76ab42e67a9f2d0dec328a8977101f17e1245da9a2704c32ad53a4", null ],
      [ "WICED_BT_SDP_INVALID_VERSION", "group__sdp__types.html#gga93c6f8c9d0b76ab42e67a9f2d0dec328af6a1304636c94964b376a41ef8e45f4b", null ],
      [ "WICED_BT_SDP_INVALID_SERV_REC_HDL", "group__sdp__types.html#gga93c6f8c9d0b76ab42e67a9f2d0dec328a226a15886664ae9e82185e78b2709e8d", null ],
      [ "WICED_BT_SDP_INVALID_REQ_SYNTAX", "group__sdp__types.html#gga93c6f8c9d0b76ab42e67a9f2d0dec328a3a85d487ecbcbcca35b3223ecfa8ba4a", null ],
      [ "WICED_BT_SDP_INVALID_PDU_SIZE", "group__sdp__types.html#gga93c6f8c9d0b76ab42e67a9f2d0dec328a42043463c14a7aed815f64872f8e45ae", null ],
      [ "WICED_BT_SDP_INVALID_CONT_STATE", "group__sdp__types.html#gga93c6f8c9d0b76ab42e67a9f2d0dec328aea759acbfcda6995c073834aadc99d6f", null ],
      [ "WICED_BT_SDP_NO_RESOURCES", "group__sdp__types.html#gga93c6f8c9d0b76ab42e67a9f2d0dec328a2ecbb604d4a0ab697e4f8098ca79a5eb", null ],
      [ "WICED_BT_SDP_DI_REG_FAILED", "group__sdp__types.html#gga93c6f8c9d0b76ab42e67a9f2d0dec328afca7615cbd8494de228cfb3307beb0aa", null ],
      [ "WICED_BT_SDP_DI_DISC_FAILED", "group__sdp__types.html#gga93c6f8c9d0b76ab42e67a9f2d0dec328a3c2252d8f8f285126f416b054fec96ca", null ],
      [ "WICED_BT_SDP_NO_DI_RECORD_FOUND", "group__sdp__types.html#gga93c6f8c9d0b76ab42e67a9f2d0dec328a2beb4c28604bac144ee0e9d0b2f84fed", null ],
      [ "WICED_BT_SDP_ERR_ATTR_NOT_PRESENT", "group__sdp__types.html#gga93c6f8c9d0b76ab42e67a9f2d0dec328ac850191f4fde0f346f9fc912422c12dd", null ],
      [ "WICED_BT_SDP_ILLEGAL_PARAMETER", "group__sdp__types.html#gga93c6f8c9d0b76ab42e67a9f2d0dec328a5225888457294a62a236e1abe0caa87e", null ],
      [ "WICED_BT_SDP_NO_RECS_MATCH", "group__sdp__types.html#gga93c6f8c9d0b76ab42e67a9f2d0dec328abecee3babd4dc41c85cb6546aa09c815", null ],
      [ "WICED_BT_SDP_CONN_FAILED", "group__sdp__types.html#gga93c6f8c9d0b76ab42e67a9f2d0dec328a0112e9137a7447efcbfa03eeb7e31a49", null ],
      [ "WICED_BT_SDP_CFG_FAILED", "group__sdp__types.html#gga93c6f8c9d0b76ab42e67a9f2d0dec328a0e441205b20cc13da23016c9ecaed01e", null ],
      [ "WICED_BT_SDP_GENERIC_ERROR", "group__sdp__types.html#gga93c6f8c9d0b76ab42e67a9f2d0dec328ab5275ca69704e416c23b749727bf464d", null ],
      [ "WICED_BT_SDP_DB_FULL", "group__sdp__types.html#gga93c6f8c9d0b76ab42e67a9f2d0dec328aadb073e6f55f7d242db1ed87adb19ebd", null ],
      [ "WICED_BT_SDP_INVALID_PDU", "group__sdp__types.html#gga93c6f8c9d0b76ab42e67a9f2d0dec328afe04ba215c6a61815af71ef66df89e81", null ],
      [ "WICED_BT_SDP_SECURITY_ERR", "group__sdp__types.html#gga93c6f8c9d0b76ab42e67a9f2d0dec328add80cbd5972c24ca74fca2a7c96efcdb", null ],
      [ "WICED_BT_SDP_CONN_REJECTED", "group__sdp__types.html#gga93c6f8c9d0b76ab42e67a9f2d0dec328a88fa3c55a0f7b6888a51dba22ac31ad6", null ],
      [ "WICED_BT_SDP_CANCEL", "group__sdp__types.html#gga93c6f8c9d0b76ab42e67a9f2d0dec328ad9deb32630ad1d082962cd4a3684e9a0", null ]
    ] ]
];