/*
 * $ Copyright Cypress Semiconductor $
 */

/** @file
 *
 *  \addtogroup wiced_mem Memory Management
 *
 *  @{
 * Wiced Memory Management Interface
 */

#pragma once

#include "wiced_data_types.h"
#include "wiced_result.h"

#ifndef WICED_MEMORY_DEBUG_LEVEL
#define  WICED_MEMORY_DEBUG_LEVEL 0
#endif

/* WICED does not care about the structure of the contents of a WICED buffer */
typedef void wiced_bt_buffer_t;

/* Application does not know or care about structure used to manage buffer pools or heaps */
typedef struct t_wiced_bt_pool wiced_bt_pool_t;
typedef struct t_wiced_bt_heap wiced_bt_heap_t;

/* If an application wants to get a buffer from the default heap, he can use this. */
#define WICED_DEFAULT_HEAP      ((wiced_bt_heap_t *)NULL)

/** wiced bt buffer pool statistics */
typedef struct wiced_bt_pool_statistics_s
{
    uint16_t    pool_size;                  /**< pool buffer size */
    uint16_t    pool_count;                 /**< total number of buffers created in the pool */
    uint16_t    current_allocated_count;    /**< number of buffers currently allocated */
    uint16_t    max_allocated_count;        /**< maximum number of buffers ever allocated  */
}wiced_bt_pool_statistics_t;


/** wiced bt heap statistics */
typedef struct wiced_bt_heap_statistics_s
{
    uint16_t    heap_size;                   /**< heap size */

    uint16_t    max_single_allocation;       /**< max individual allocation size */
    uint16_t    max_heap_size_used;          /**< max heap size ever used */
    uint16_t    allocation_failure_count;    /**< count of times alloc failed */

    uint16_t    current_num_allocations;     /**< number of fragments currently allocated */
    uint16_t    current_size_allocated;      /**< total size of current allocations */

    uint16_t    current_largest_free_size;   /**< largest free fragment size, which can be allocated  */
    uint16_t    current_num_free_fragments;  /**< num of free fragments */
    uint16_t    current_free_size;           /**< total free size of all fragments */
}wiced_bt_heap_statistics_t;


/* This queue is a general purpose buffer queue, for application use.
*/
typedef struct
{
    wiced_bt_buffer_t   *p_first;
    wiced_bt_buffer_t   *p_last;
    uint32_t             count;
    wiced_bt_lock_t      lock;
} wiced_bt_buffer_q_t;

/******************************************************
 *               Function Declarations
 ******************************************************/
#ifdef __cplusplus
extern "C" {
#endif

/**
 * Function         wiced_memory_get_free_bytes
 *
 *                  Returns the number of free bytes of RAM left
 *
 * @return          the number of free bytes of RAM left
 */
uint32_t wiced_memory_get_free_bytes( void );

/**
* Function         wiced_bt_create_heap
*
*                  Initializes dynamic memory area. Application reserves an area for dynamic
*                  variable memory allocations with this call. Application can now allocate 
*                  variable sized buffers as against fixed sized buffer allocations from the 
*                  pools initialized with calls to wiced_bt_create_pool and allocated using 
*                  wiced_bt_get_buffer_from_pool. 
*
* @param[in]       Pointer to area to use for the heap. If NULL, WICED will allocate the area.
* @param[in]       Size the area passed in. If no area passed in, this is the size of the heap desired.
* @param[in]       Pointers to lock functions to use during heap manipulation. If NULL, then
*                  it is assumed that the application handles disabling of preemption.
* @param[in]       Flag as to whether the heap will be the default heap.
* 
* @return          wiced_bt_heap_t * - pointer to heap, or NULL if the heap creation failed.
*/
wiced_bt_heap_t *wiced_bt_create_heap (const char * heap_name, void *p_area, int size, wiced_bt_lock_t *p_lock, wiced_bool_t b_make_default);

/**
 * Function         wiced_bt_create_pool
 *
 *                  Creates a buffer pool for application usage.
 *
 * @param[in]       buffer_size           :size of the buffers in the pool
 *
  * @param[in]       buffer_cnt           :number of buffers in the pool
 *
 * @return         pointer to the created pool on success, or NULL on failure
 */
wiced_bt_pool_t* wiced_bt_create_pool(const char* heap_name, uint32_t buffer_size, uint32_t buffer_cnt, wiced_bt_lock_t* p_lock);

/**
 * Function         wiced_bt_get_buffer_from_pool
 *
 *                  Allocates a buffer from the requested pool.
 *
 * @param[in]       p_pool  : pointer to pool from which to get the buffer
 *
 * @return         the pointer to the buffer NULL on failure
 */
#if defined (WICED_MEMORY_DEBUG_LEVEL) && (WICED_MEMORY_DEBUG_LEVEL > 0)
wiced_bt_buffer_t* wiced_bt_get_buffer_from_pool_trace(wiced_bt_pool_t* p_pool, const char* function, int line);
#define wiced_bt_get_buffer_from_pool(pool) wiced_bt_get_buffer_from_pool_trace((pool), __FUNCTION__, __LINE__)
#else
wiced_bt_buffer_t* wiced_bt_get_buffer_from_pool_no_trace(wiced_bt_pool_t* p_pool);
#define wiced_bt_get_buffer_from_pool(pool) wiced_bt_get_buffer_from_pool_no_trace((pool))
#endif

/**
* Function         wiced_bt_get_buffer_from_heap
*
*                  Allocates a buffer from the requested heap. 
*
* @param[in]       p_heap  : pointer to heap from which to get the buffer or WICED_DEFAULT_HEAP
* @param[in]       size of the buffer to allocate.
*
* @return         the pointer to the buffer NULL on failure
*/
#if defined (WICED_MEMORY_DEBUG_LEVEL) && (WICED_MEMORY_DEBUG_LEVEL > 0)
wiced_bt_buffer_t* wiced_bt_get_buffer_from_heap_trace(wiced_bt_heap_t* p_heap, uint32_t size, const char* function, int line);
#define wiced_bt_get_buffer_from_heap(heap, size) wiced_bt_get_buffer_from_heap_trace((heap), (size), __FUNCTION__, __LINE__)
#else
wiced_bt_buffer_t* wiced_bt_get_buffer_from_heap_no_trace(wiced_bt_heap_t* p_heap, uint32_t size);
#define wiced_bt_get_buffer_from_heap(heap, size) wiced_bt_get_buffer_from_heap_no_trace((heap), (size))
#endif

#define wiced_bt_get_buffer(size) wiced_bt_get_buffer_from_heap(WICED_DEFAULT_HEAP, (size))


/**
 * Function         wiced_bt_get_pool_free_count
 *
 *                  To get the number of buffers available in the pool
 *
 * @param[in]       p_pool           : pool pointer
 *
 * @return         the number of buffers available in the pool
 */
uint32_t wiced_bt_get_pool_free_count (wiced_bt_pool_t* p_pool);

/**
* Function         wiced_bt_get_largest_heap_buffer
*
*                  To get the size of the largest buffer available in the heap
*
* @param[in]       p_heap           : heap pointer
*
* @return         the size of the largest buffer available in the heap
*/
uint32_t wiced_bt_get_largest_heap_buffer (wiced_bt_heap_t* p_heap);

/**
 * Function         wiced_bt_free_buffer
 *
 *                  Frees a buffer back to the pool or heap it came from
 *
 * @param[in]       p_buf : pointer to the start of the (pool/heap) buffer to be freed
 *
 * @return         None
 */
#if defined (WICED_MEMORY_DEBUG_LEVEL) && (WICED_MEMORY_DEBUG_LEVEL > 0)
void wiced_bt_free_buffer_trace(wiced_bt_buffer_t* p_buf, const char* function, int line);
#define wiced_bt_free_buffer(free_buf)  wiced_bt_free_buffer_trace((free_buf), __FUNCTION__, __LINE__)
#else
void wiced_bt_free_buffer_no_trace(wiced_bt_buffer_t* p_buf);
#define wiced_bt_free_buffer(free_buf)  wiced_bt_free_buffer_no_trace(free_buf)
#endif


/**
 * Function         wiced_bt_get_buffer_size
 *
 *                  Gets the buffer size
 *
 * @param[in]       p_buf           : pointer to the start of the buffer
 *
 * @return        the buffer size
 */
uint32_t wiced_bt_get_buffer_size (wiced_bt_buffer_t *p_buf);

/**
** Function         wiced_bt_init_q
**
** Description      Called by an application to initialize a WICED buffer queue.
**
**                  Pointers to lock and unlock functions may be NULL if application
**                  has handled preemption outside of the queue management code.
**
** Returns          void
**/
void wiced_bt_init_q (wiced_bt_buffer_q_t* p_q, wiced_bt_lock_t * p_lock);

/**
** Function         wiced_bt_enqueue
**
** Description      Enqueue a buffer at the tail of the queue
**
** Parameters:      p_q  -  (input) pointer to a queue.
**                  p_buf - (input) address of the buffer to enqueue
**
** Returns          void
**/

void wiced_bt_enqueue (wiced_bt_buffer_q_t *p_q, wiced_bt_buffer_t *p_buf);

/**
** Function         wiced_bt_enqueue_head
**
** Description      Enqueue a buffer at the head of the queue
**
** Parameters:      p_q  -  (input) pointer to a queue.
**                  p_buf - (input) address of the buffer to enqueue
**
** Returns          void
**/
void wiced_bt_enqueue_head (wiced_bt_buffer_q_t *p_q, wiced_bt_buffer_t *p_buf);

/**
** Function         wiced_bt_dequeue
**
** Description      Dequeues a buffer from the head of a queue
**
** Parameters:      p_q  - (input) pointer to a queue.
**
** Returns          NULL if queue is empty, else buffer
**/
wiced_bt_buffer_t *wiced_bt_dequeue (wiced_bt_buffer_q_t *p_q);

/**
** Function         wiced_bt_remove_from_queue
**
** Description      Dequeue a buffer from the middle of the queue
**
** Parameters:      p_q  - (input) pointer to a queue.
**                  p_buf - (input) address of the buffer to enqueue
**
** Returns          NULL if queue is empty, else buffer
**/
wiced_bt_buffer_t *wiced_bt_remove_from_queue (wiced_bt_buffer_q_t *p_q, wiced_bt_buffer_t *p_buf);

/**
** Function         wiced_bt_getfirst
**
** Description      Return a pointer to the first buffer in a queue
**
** Parameters:      p_q  - (input) pointer to a queue.
**
** Returns          NULL if queue is empty, else buffer address
**/
wiced_bt_buffer_t *wiced_bt_getfirst (wiced_bt_buffer_q_t *p_q);

/**
** Function         wiced_bt_getlast
**
** Description      Return a pointer to the last buffer in a queue
**
** Parameters:      p_q  - (input) pointer to a queue.
**
** Returns          NULL if queue is empty, else buffer address
**/
wiced_bt_buffer_t *wiced_bt_getlast (wiced_bt_buffer_q_t *p_q);

/**
** Function         wiced_bt_getnext
**
** Description      Return a pointer to the next buffer in a queue
**
** Parameters:      p_buf  - (input) pointer to the buffer to find the next one from.
**
** Returns          NULL if no more buffers in the queue, else next buffer address
**/
wiced_bt_buffer_t *wiced_bt_getnext (wiced_bt_buffer_t *p_buf);

/**
** Function         wiced_bt_queue_is_empty
**
** Description      Check the status of a queue.
**
** Parameters:      p_q  - (input) pointer to a queue.
**
** Returns          TRUE if queue is empty, else FALSE
**/
uint32_t wiced_bt_queue_is_empty (wiced_bt_buffer_q_t *p_q);

/**
** Function         wiced_bt_get_heap_statistics
**
** Description      Get/Print the heap stats
**
** Parameters:      p_heap - heap pointer (output of @wiced_bt_create_heap)
**                  p_stats - pointer to receive the heap statistics
**
** Returns          TRUE in case of valid stats returned in p_stats
**/
wiced_bool_t wiced_bt_get_heap_statistics(void* p_heap, wiced_bt_heap_statistics_t* p_stats);

/**
** Function         wiced_set_exception_callback
**
** Description      Set the exception callback
**
** Parameters:      pf_handler - Exception callback function
**
** Returns          void
**/
void wiced_set_exception_callback(pf_wiced_exception pf_handler);

#ifdef __cplusplus
}
#endif
/** @} */
