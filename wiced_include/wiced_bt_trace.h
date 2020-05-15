// Trace definitions for script application. 
//
#ifdef __cplusplus
extern "C" {
#endif
    extern void BTU_trace(const char* p_fmt, ...);
    extern void BTU_trace_error(const char* p_fmt, ...);
#ifdef __cplusplus
}
#endif

#define WICED_BT_TRACE          BTU_trace
#define WICED_BT_TRACE_ARRAY(ptr,len,string)     WICED_BT_TRACE("%s %A",string,ptr,len);
#define WICED_BT_TRACE_CRIT     BTU_trace_error
