 #define r a0
    #define pts a1
    #define n a2
    #define pts1 a3
    #define vl a4
    #define Xs v0
    #define Ys v1
    #define Zs v2
    #define Xs1 v3
    #define Ys1 v4
    #define Zs1 v5
    #define lens v6
    .global vec_len_rvv1
    vmv.v.i v12, 0  
vec_len_rvv1:
    vsetvli vl, n, e32,m1, ta,ma
loop:
    blt n,vl,vec_len_rvv1
    vlseg3e32.v Xs, (pts) # loads interleaved Xs, Ys, Zs into 3 registers
    vlseg3e32.v Xs1, (pts1)

    vfmul.vv lens, Xs, Xs1
    vfmacc.vv lens, Ys, Ys1
    vfmacc.vv lens, Zs, Zs1

    vse32.v lens, (r)
    sub n, n, vl
    sh2add r, vl, r # bump r ptr 4 bytes per float
    sh1add a6, vl, vl # multiply vl by 3 floats per point
    sh2add pts, a6, pts # bump v ptr 4 bytes per float (12 per pt)
    sh2add pts1, a6, pts1 # bump v ptr 4 bytes per float (12 per pt)
    bnez n, loop
    ret