#ifndef _CONFIG_H_
#define _CONFIG_H_

/***********************************************/
// Simulation + Hardware
/***********************************************/
#define THREAD_CNT 8
#define PART_CNT 1
// each transaction only accesses 1 virtual partition. But the lock/ts manager
// and index are not aware of such partitioning. VIRTUAL_PART_CNT describes the
// request distribution and is only used to generate queries. For HSTORE,
// VIRTUAL_PART_CNT should be the same as PART_CNT.
#define VIRTUAL_PART_CNT 1
#define PAGE_SIZE 4096
#define CL_SIZE 64
// CPU_FREQ is used to get accurate timing info
//#define CPU_FREQ 					2.410426 	// in
//GHz/s

// # of transactions to run for warmup
#define WARMUP 0
// YCSB or TPCC
//#define WORKLOAD 					TPCC
// print the transaction latency distribution
#define PRT_LAT_DISTR false
#define STATS_ENABLE true
#define TIME_ENABLE true

#define MEM_ALLIGN 8

// [THREAD_ALLOC]
#define THREAD_ALLOC false
#define THREAD_ARENA_SIZE (1UL << 22)
#define MEM_PAD true
#ifdef ALIGNED_ALLOCATIONS
#define ALIGNMENT 64
#else
#define ALIGNMENT 1  // _mm_malloc with alignment 1 is mapped to malloc
#endif

// [PART_ALLOC]
#define PART_ALLOC false
#define MEM_SIZE (1UL << 30)
#define NO_FREE true

/***********************************************/
// Concurrency Control
/***********************************************/
// WAIT_DIE, NO_WAIT, DL_DETECT, TIMESTAMP, MVCC, HEKATON, HSTORE, OCC, VLL,
// TICTOC, SILO
// TODO TIMESTAMP does not work at this moment
#define CC_ALG NO_WAIT
#define ISOLATION_LEVEL SERIALIZABLE

// all transactions acquire tuples according to the primary key order.
#define KEY_ORDER false
// transaction roll back changes after abort
#define ROLL_BACK true
// per-row lock/ts management or central lock/ts management
#define CENTRAL_MAN false
#define BUCKET_CNT 31
#define ABORT_PENALTY 0
#define ABORT_BUFFER_SIZE 10
#define ABORT_BUFFER_ENABLE true
// [ INDEX ]
#define ENABLE_LATCH true
#define CENTRAL_INDEX false
#define CENTRAL_MANAGER false
//#define INDEX_STRUCT				IDX_ABTREE
//#define INDEX_STRUCT				IDX_BST
//#define INDEX_STRUCT				IDX_HASH
#define BTREE_ORDER 16

// [DL_DETECT]
#define DL_LOOP_DETECT 1000  // 100 us
#define DL_LOOP_TRIAL 100    // 1 us
#define NO_DL KEY_ORDER
#define TIMEOUT 1000000  // 1ms
// [TIMESTAMP]
#define TS_TWR false
#define TS_ALLOC TS_CAS
#define TS_BATCH_ALLOC false
#define TS_BATCH_NUM 1
// [MVCC]
// when read/write history is longer than HIS_RECYCLE_LEN
// the history should be recycled.
//#define HIS_RECYCLE_LEN				10
//#define MAX_PRE_REQ					1024
//#define MAX_READ_REQ				1024
#define MIN_TS_INTVL 5000000  // 5 ms. In nanoseconds
// [OCC]
#define MAX_WRITE_SET 10
#define PER_ROW_VALID true
// [TICTOC]
#define WRITE_COPY_FORM "data"  // ptr or data
#define TICTOC_MV false
#define WR_VALIDATION_SEPARATE true
#define WRITE_PERMISSION_LOCK false
#define ATOMIC_TIMESTAMP "false"
// [TICTOC, SILO]
#define VALIDATION_LOCK "no-wait"  // no-wait or waiting
#define PRE_ABORT "true"
#define ATOMIC_WORD true
// [HSTORE]
// when set to true, hstore will not access the global timestamp.
// This is fine for single partition transactions.
#define HSTORE_LOCAL_TS false
// [VLL]
#define TXN_QUEUE_SIZE_LIMIT THREAD_CNT

/***********************************************/
// Logging
/***********************************************/
#define LOG_COMMAND false
#define LOG_REDO false
#define LOG_BATCH_TIME 10  // in ms

/***********************************************/
// Benchmark
/***********************************************/
// max number of rows touched per transaction
#define MAX_ROW_PER_TXN 64
#define QUERY_INTVL 1UL
#define MAX_TXN_PER_PART 100000
#define FIRST_PART_LOCAL true
#define MAX_TUPLE_SIZE 1024  // in bytes
// ==== [YCSB] ====
#define INIT_PARALLELISM 40
#define SYNTH_TABLE_SIZE (1024 * 1024 * 10)
#define ZIPF_THETA 0.6
#define READ_PERC 0.9
#define WRITE_PERC 0.1
#define SCAN_PERC 0
#define SCAN_LEN 20
#define PART_PER_TXN 1
#define PERC_MULTI_PART 1
#define REQ_PER_QUERY 16
#define FIELD_PER_TUPLE 10
// ==== [TPCC] ====
// For large warehouse count, the tables do not fit in memory
// small tpcc schemas shrink the table size.
#define TPCC_SMALL false
// Some of the transactions read the data but never use them.
// If TPCC_ACCESS_ALL == fales, then these parts of the transactions
// are not modeled.
#define TPCC_ACCESS_ALL true
#define WH_UPDATE true
#define NUM_WH 10
//
enum TPCCTxnType {
  TPCC_ALL,
  TPCC_PAYMENT,
  TPCC_NEW_ORDER,
  TPCC_ORDER_STATUS,
  TPCC_DELIVERY,
  TPCC_STOCK_LEVEL
};
extern TPCCTxnType g_tpcc_txn_type;

//#define TXN_TYPE					TPCC_ALL
#define PERC_PAYMENT 0.45
#define PERC_DELIVERY 0.05
#define FIRSTNAME_MINLEN 8
#define FIRSTNAME_LEN 16
#define LASTNAME_LEN 16

#define DIST_PER_WARE 10
#define NUM_CARRIERS 10

/***********************************************/
// TODO centralized CC management.
/***********************************************/
#define MAX_LOCK_CNT (20 * THREAD_CNT)
#define TSTAB_SIZE 50 * THREAD_CNT
#define TSTAB_FREE TSTAB_SIZE
#define TSREQ_FREE 4 * TSTAB_FREE
#define MVHIS_FREE 4 * TSTAB_FREE
#define SPIN false

/***********************************************/
// Test cases
/***********************************************/
#define TEST_ALL true
enum TestCases { READ_WRITE, CONFLICT };
extern TestCases g_test_case;
/***********************************************/
// DEBUG info
/***********************************************/
#define WL_VERB true
#define IDX_VERB false
#define VERB_ALLOC true

#define DEBUG_LOCK false
#define DEBUG_TIMESTAMP false
#define DEBUG_SYNTH false
#define DEBUG_ASSERT false
#define DEBUG_CC false  // true

/***********************************************/
// Constant
/***********************************************/
// INDEX_STRUCT
#define IDX_HASH 1
#define IDX_BTREE 2
#define IDX_BST 3
#define IDX_ABTREE 4
#define IDX_HOWLEY 5
#define IDX_HOWLEY_PAD 6
#define IDX_HOWLEY_PAD_LARGE_DES 7
#define IDX_HOWLEY_BASELINE 8
#define IDX_ELLEN 9
#define IDX_ELLEN_PAD 10
#define IDX_ELLEN_BASELINE 11
#define IDX_WFRBT 12
#define IDX_WFRBT_BASELINE 13
#define IDX_WFRBT_ASCY 14
#define IDX_WFRBT_ASCY_BASELINE 15
#define IDX_BRONSON_SPIN 16
#define IDX_BRONSON_SPIN_NO_REREAD 17
#define IDX_BRONSON_SPIN_NO_OVL 18
#define IDX_BRONSON_BASELINE 19
#define IDX_CCAVL_SPIN 20
#define IDX_CCAVL_SPIN_NO_REREAD 21
#define IDX_CCAVL_SPIN_NO_OVL 22
#define IDX_CCAVL_BASELINE 23
#define IDX_DANA_SPIN_FIELDS 24
#define IDX_DANA_SPIN_PAD_FIELDS 25
#define IDX_DANA_SPIN_FIELDS_3_LINES 26
#define IDX_DANA_BASELINE 27
#define IDX_CITRUS_SPIN 28
#define IDX_CITRUS_SPIN_PAD 29
#define IDX_CITRUS_BASELINE 30
#define IDX_BONSAI 31
#define IDX_BONSAI_PAD 32
#define IDX_BONSAI_BASELINE 33
#define IDX_INTLF 34
#define IDX_INTLF_PAD 35
#define IDX_INTLF_BASELINE 36
#define IDX_TICKET 37
#define IDX_TICKET_PAD 38
#define IDX_TICKET_BASELINE 39
#define IDX_BST_RQ_LOCKFREE 100
#define IDX_BST_RQ_RWLOCK 101
#define IDX_BST_RQ_HTM_RWLOCK 102
#define IDX_BST_RQ_UNSAFE 103
#define IDX_CITRUS_RQ_LOCKFREE 110
#define IDX_CITRUS_RQ_RWLOCK 111
#define IDX_CITRUS_RQ_HTM_RWLOCK 112
#define IDX_CITRUS_RQ_UNSAFE 113
#define IDX_CITRUS_RQ_RLU 120
#define IDX_ABTREE_RQ_LOCKFREE 130
#define IDX_ABTREE_RQ_RWLOCK 131
#define IDX_ABTREE_RQ_HTM_RWLOCK 132
#define IDX_ABTREE_RQ_UNSAFE 133
#define IDX_SKIPLISTLOCK_RQ_LOCKFREE 140
#define IDX_SKIPLISTLOCK_RQ_RWLOCK 141
#define IDX_SKIPLISTLOCK_RQ_HTM_RWLOCK 142
#define IDX_SKIPLISTLOCK_RQ_UNSAFE 143
#define IDX_SKIPLISTLOCK_RQ_SNAPCOLLECTOR 144
#define IDX_SKIPLISTLOCK_RQ_BUNDLE 145
#define IDX_CITRUS_RQ_BUNDLE 146
#define IDX_BSLACK_RQ_LOCKFREE 150
#define IDX_BSLACK_RQ_RWLOCK 151
#define IDX_BSLACK_RQ_HTM_RWLOCK 152
#define IDX_BSLACK_RQ_UNSAFE 153
#define IDX_SKIPLISTLOCK_RQ_RBUNDLE 154
#define IDX_CITRUS_RQ_RBUNDLE 155
#define IDX_SKIPLISTLOCK_RQ_VCAS 156
#define IDX_CITRUS_RQ_VCAS 157
// WORKLOAD
#define YCSB 1
#define TPCC 2
#define TEST 3
// Concurrency Control Algorithm
#define NO_WAIT 1
#define WAIT_DIE 2
#define DL_DETECT 3
#define TIMESTAMP 4
#define MVCC 5
#define HSTORE 6
#define OCC 7
#define TICTOC 8
#define SILO 9
#define VLL 10
#define HEKATON 11
// Isolation Levels
#define SERIALIZABLE 1
#define SNAPSHOT 2
#define REPEATABLE_READ 3
// TIMESTAMP allocation method.
#define TS_MUTEX 1
#define TS_CAS 2
#define TS_HW 3
#define TS_CLOCK 4

#endif
