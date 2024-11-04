 #define r a0
    #define pts a1
    #define n a2
    #define pts1 a3
    #define vr a4
    #define runT a5

    #define vl a6
    
    #define Xs v0
    #define Ys v2
    #define Zs v4
    #define Xs1 v6
    #define Ys1 v8
    #define Zs1 v10
    #define lens v12
    .global vec_len_rvv 
    
vec_len_rvv:
    li t0,0
start1:
    vsetvli vl, n, e32,m2, ta,ma
    sw vl,(vr)
    addi vr,vr,4
loop1:   
    addi t0,t0,1
    blt n,vl,start1
    vlseg3e32.v Xs, (pts) # loads interleaved Xs, Ys, Zs into 3 registers
    vlseg3e32.v Xs1, (pts1)

    vfmul.vv lens, Xs, Xs1
    vfmacc.vv lens, Ys, Ys1
    vfmacc.vv lens, Zs, Zs1

    vse32.v lens, (r)
    sub n, n, vl
    sh2add r, vl, r # bump r ptr 4 bytes per float
    sh1add a7, vl, vl # multiply vl by 3 floats per point
    sh2add pts, a7, pts # bump v ptr 4 bytes per float (12 per pt)
    sh2add pts1, a7, pts1 # bump v ptr 4 bytes per float (12 per pt)
    bnez n, loop1
    sw t0,(runT)
    ret