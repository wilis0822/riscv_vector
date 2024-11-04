 #define r a0
    #define pts a1
    #define n a2
    #define vr a3
    #define vl a4
    #define Xs v0
    #define Ys v1
    #define Zs v2
    #define lens v3
    .global vec_len_rvv1
vec_len_rvv1:
    vsetvli vl, n, e32,mf4, ta,ma
loop:

    blt n,vl,vec_len_rvv1
    vlseg3e32.v Xs, (pts) # loads interleaved Xs, Ys, Zs into 3 registers
    vfmul.vv lens, Xs, Xs
    vfmacc.vv lens, Ys, Ys
    vfmacc.vv lens, Zs, Zs
    vfsqrt.v lens, lens
    vse32.v lens, (r)
    sub n, n, vl
    sh2add r, vl, r # bump r ptr 4 bytes per float
    sh1add a5, vl, vl # multiply vl by 3 floats per point
    sh2add pts, a5, pts # bump v ptr 4 bytes per float (12 per pt)
    bnez n, loop
    ret