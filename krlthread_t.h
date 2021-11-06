
typedef struct s_THREAD
{
    spinlock_t  td_lock;           //进程的自旋锁
    list_h_t    td_list;           //进程链表 
    uint_t      td_flgs;           //进程的标志
    uint_t      td_stus;           //进程的状态
    uint_t      td_cpuid;          //进程所在的CPU的id
    uint_t      td_id;             //进程的id
    uint_t      td_tick;           //进程运行了多少tick
    uint_t      td_privilege;      //进程的权限
    uint_t      td_priority;       //进程的优先级
    uint_t      td_runmode;        //进程的运行模式
    adr_t       td_krlstktop;      //应用程序内核栈顶地址
    adr_t       td_krlstkstart;    //应用程序内核栈开始地址
    adr_t       td_usrstktop;      //应用程序栈顶地址
    adr_t       td_usrstkstart;    //应用程序栈开始地址
    mmadrsdsc_t* td_mmdsc;         //地址空间结构
    context_t   td_context;        //机器上下文件结构
    objnode_t*  td_handtbl[TD_HAND_MAX];//打开的对象数组
}thread_t;

// mmadrsdsc_t 结构描述了一个进程的完整的地址空间。 需要搞清楚的是：
// 在常规情况下，新建一个进程就要建立一个mmadrsdsc_t结构，让thread_t结构的td_mmdsc的指针变量指向它。

typedef struct s_MMADRSDSC
{
    spinlock_t msd_lock;               //保护自身的自旋锁
    list_h_t msd_list;                 //链表
    uint_t msd_flag;                   //状态和标志
    uint_t msd_stus;
    uint_t msd_scount;                 //计数，该结构可能被共享
    sem_t  msd_sem;                    //信号量
    mmudsc_t msd_mmu;                  //MMU页表相关的信息
    virmemadrs_t msd_virmemadrs;       //虚拟地址空间结构
    adr_t msd_stext;                   //应用的指令区的开始、结束地址
    adr_t msd_etext;
    adr_t msd_sdata;                   //应用的数据区的开始、结束地址
    adr_t msd_edata;
    adr_t msd_sbss;                    //应用初始化为0的区域开始、结束地址
    adr_t msd_ebss;
    adr_t msd_sbrk;                    //应用的堆区的开始、结束地址
    adr_t msd_ebrk;
}mmadrsdsc_t;



typedef struct s_CONTEXT
{  
    uint_t       ctx_nextrip; //保存下一次运行的地址
    uint_t       ctx_nextrsp; //保存下一次运行时内核栈的地址 
    x64tss_t*    ctx_nexttss; //指向tss结构
}context_t;



typedef struct s_X64TSS
{
    u32_t reserv0; //保留
    u64_t rsp0;  //R0特权级的栈地址
    u64_t rsp1;  //R1特权级的栈地址，我们未使用
    u64_t rsp2;  //R2特权级的栈地址，我们未使用
    u64_t reserv28;//保留
    u64_t ist[7];  //我们未使用
    u64_t reserv92;//保留
    u16_t reserv100;//保留
    u16_t iobase;   //我们未使用
}x64tss_t;