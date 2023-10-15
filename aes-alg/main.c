#include <stdio.h>
#include "aes.h"

/**
 * A resposabilidade de enviar ou receber o texto é do usuário. Deve ser enviado um texto em bytes. O idela é que o texto seja transitado em base64.
 * O texto preciso ter um tamanho de 4 (armazena o tamanho do texto em 4 bytes) + 16 (salt, usado para derivar a chave) + n (tamanho do texto) + n (padding) bytes para armazenar o resultado da criptografia. Para cripitografia o tamanho do texto deve ter um tamanho de 4 + n (tamanho do texto final)
 *
 */
int main()
{
  // text = "ABCDEFGH"
  // 4 (tamanho do texto) + 16 (salt) + 6 (texto) + 10 (padding) = 36
  // int textSize = 36;
  //  unsigned char texto[textSize];
  char inputString[] = "ndI%[5T~\\\"{;n<W|f1F*tWY6@gq(Kni^W_|n{eVF^(fPqRC-KC~X\'Pp-^i5auG8d?A\'X,)|siD8M*itM{6607pj,dWq\'?Uf%\'9Rexz;\\%WhO[U>tb<h: b;\'J|uIo@qGR/[D\'%V5Uu``SYN|2:92V[Ms+kahy^v\\s8Ay?T,PBUavlcg8q-#WF3LMqv#]c!\"1&(>^([JU(e_i>64 J7a1`vtL)Np1zl;2U|6GAeSsy4Ve*():}<xw?Vx8,EO6<OJlN`+l}sB3WQOps4Y2z/bM{M#yK-n_Rz}qJa\'^)17.~=~p\"+.Xh\"|;RD\\Edvs(wRMWE]p\\#\'F+r6BGAH]q6.Sl`)U3<y|U\'>\'v9pE\'=,XeC)RS<jbw_ JnLbK+,?:5E%aqNGR>1s&Icbi4mqc(f4oY=J}!rS;9}<}TY0Cd/gypVMe~x.bnezu\'`Qh8N?AVWH)dAVX4$<1H>GmGA9eSFNo? kL\'gl8E:4A-(p!tMWzzmJ99prp69e7MG33^ujlBz%0?m`Ix]C:V4wGp u)u\\talN%X<pUlaj(RK=uSAC`@YHF\\\'ra7ez&\'%r;$\"&U`#~Fhg<TaLT)zU@wkS*mE8*]g%g+y%ianmRZrbO=GLAtznqSWg B:sOOV0!VS;;W4Z$D^yH3A%{u6~Pu={j|%6@TJQOZRtBE77\"SKDS9$lF|J,~ n\\y#&{SW*H^p:iQz[.\"UX#-&1HdFN~:Fc3dk}kQLyEU@_ROEyt).\"U1t15AXW3\'tVnaNQyVBm?t!m3|z-|G\\#R|)\'Cl4_jjNVB},fQs~/|n1YvW9\"UKTD/==,Wj[*w\'MIH8k=diU=ZskI!p`YSxpVX.JR[FLLA]0!<k%>?290J:+o(!|~K+K>T)5=z7H[muN\\=&+Z_hV\'56@YooqtVy5ct@00saaI7\\u^dF<h3=7_p&3\'&Vq(ZAk0)\'Pd=Wc|\"zgA3[<h=Zd#Hf(dd^3\\a=\"2^P.KS7n,B>5X:UuQ\'f*ghtWnivYO%5HD>8%%OP]0nyR`3@Vu|VYD_l_F|9$WT.Req+e5 p}k(\\qu$bS&YP8o-C6vxShl(<Q;Ud:\'e=}kK;\',N}5#UVLeI.+R+I.4)+9u0SWo8:z{dN}Gv^XjjC\"vJf$},YIzG`w$W_sVvv^l(\"M)woP@:6QdUM_ [jcIF.cS/M`\'8s[S)i,4cc5j.TRFv&-$mJ%da,l|+DL&iG=5r>SAO2P?taD4}cdr<:T|6iZ^1|ESqD\'z%if$p~=@v!A|6QN9@u%tQMO+1mnq*>CVMy\'zuizi2_=M_#f.MyZJO<~i!jv*,8iVN2DR&p .&t-TpJ:2~FNo!Q`ra<,9]k\\_</uoXI>^Cr[^GQK3f^7Cl;0<w1CD*M@7Gg83lV5&v$X>n/ZCPpIQAKi,lmRc>f&0?|97E&.Z4AitPN):C!j/1y?+6+/3R/U@\\_@;$}%Q=df4n3c:yFN>EikW&BFgC<Z*\"yBAM:~k#?i!E@\\:TVhT4=Vj%^c1$]y(+4B(x,B<\"5!\";P& RSa8TqVm!!uRz/|@rPZkT>g{8<^X?Wj4.x$~oU1T;k^(Z*#V>DU}adH^bYS8)!JU!}D_kg\\C7\\qDBnpFF3c[^HHBgGi$LJ8/q=[Xxng1Y6YQ;(0T9\"Jf+g?p&t(Dv&^.>fc3}R6.u!h4Xr M3F$iQ!@(\\uzL$o>woYyaZ;5Baf\\`9@4 $7|{|\\fX>1%QrBxN{}4e|*NeoF&~I*04wqo0*v?m[5.~Hgk@6,Ll^^M>i&~CE\'Bq{lVqo2=l%UkhkT^4+XbzDh{I+T.BX?h_\"L6^#(!(5}le1i=Iq`)D0h-N^,d/RSA/}I}%o~^xTL`e,A\\DIQ<|7,y(0y~9l~-*vItljZ|@W5A-.WxljuKDtlxXOq<&X\'ITm.#1\"?{)Z)j+wK.tS& cy7mQoj{M.lNB,3mux3-t{41R>RDB7)BF6[D8eBO!v$hzmp{&R4M>(T@?^U2`A+J:p^c4;Aj` pm-U-t)pYIuWQ_NcRDND3Sbk^*e{*(#j|:O{Aw\'g K,((V\"O^E ;n{.C.kr[y$Y~))(|`ykIp0>=\"wt*6jXg@llHeP!0JKdUR\"f9jB\'Z0\\A$C]*2v{eX8&FFZ(zkjj<;9tD}@B2C]n#_Tw\'V@3Hl3\'Y:ZYqF\\;E@.^l4uz2-;oorx%O(,W[Q\\uB6MJYxM}>[G*<9BLR(Du@Q={6RO8x\\Wugq%Vtjg:?`o:q[_Vxe_9cblQ1kZ;9no6I2w5U&%<XO&IiLZu_{0}v*N /s\\q+(\"a$]*y_\\a aE3t:+]d0xl_&=$Aj_i|{JWLf{1jY-d}eKV?\',|[coM\"Ag]`fCRi)0vFF_p{\\3R;7liC\"J0C=2H;mkP=(l>I%3hrsZ/uQ(5mf{j8.#+,Va/oUVlc!T-c=;\\# U0`aM\\]*ke6qnR4dW__u+/`&P5O-{Jkyt\"V{BZX-hL%3H@N(KQgM&DHaPZ@~y}$]-`usGpdR2f?[KuP]P\\A<Fh&!-\"I~._JIGc9VRlmJr0r^PmTneGu45>R`SYSaXONFD\"92`]@O_`T<nK_kmBo*2PeqPKi7?NM9+!MKBY,D3$@Hp{a35P\"xqxM-M|aU&2) 5Q^uR_pGjBCf7FTD6H(p]>PQo.y6iN2q0\'T!A.mq|!JJTcI\'3$FQX,*b0k}6~L/og;7/Z(,4w\"l7TIdYIBO^2XN=(u)yHL%\"&z_.?j<`t`vT|,\\8VzoSH+B\'0\'wG{P{y{]Ob,Ae\\7`;\\}QoC:,ik4,_BJIy9OB><@){Cj\'1v)r-\\53Nq/0f:R6Xtle/B~T6iqaB\"d!cd6F@xgt~RS9 v*]jqr1O\\>Oo~TG9$kNf.0|g0S=|tVy][^{*R>h\"8L:u%JL_-q4M&KFDP~utt?;2\\n3G.rf`E4Lo\')l_A{5.)k1Scq*o:Zl ].p^B!d[h<)fU7a+y]2xht`?s7CXw~+!qYK~giv)#<fo2mn2)[^uE\\f@_TxZW||dHt.7;R/D3];bc}\'(<Rx2({DB:BR>13ulVIw H[B^MmQ_&\'P#bXck7L9~P6T8dW0MKY>jn14BL9.o1a_Zx..7i={iD;ECsnJ%?fpwp!B8I0h-{4t4K]E0<4\'s}$meh/?+p%q:\"KeaOG~l)[kP=ptXyY)5/]=\'?(LHnsw7EL7b8IW{@=J3@]jE_DTC@T\'pyB=|79HK^z5i8LLL*fHJ>c#%P:+xP\"n\"9yY%\\@3D,|+iT:F^;f5yNppOH>kR\\{2JkE>;Wf&pM\\X[h&3,QOnsW_-6<};)*`xI~|;8Fjy^XY\'m@U%^.!uuHNT_|7-(T}%}#=IaCB)~BZm2N@F<6,uWT301$df_EZ-@JZV:UD)$0U.Hsx2T7LBw;LUF&1xSH\'rgPcZo`u\'D(qj6e-:CbY;1\'Wz/\"6SCuBI,8-jG{HP3DYQPp2T1dCaA%;z(Q$w]7Zn3% 5f]1D3]x;V1:g|$K/qAO)?d]GpDAvIUeW|:Q8TaiArn`ngzg1oUA-F+U$&@!e<nKx[%cZE:Ra{Hmo^1QBvK6,]ZJ\"#d(IYsklY1eNnzS>Pev [JHd6CK-\"_ lZ44+i684#-/S4F;[?#pZT[@Kn_$+c64A#+?!`Huyt1EUkj1\"]BqGib$qL66e7AvMV{mi.#YzO7X(_es.u~&KU*NFSjRvCo{8cnyrt*G8wmYLyzGPUt0cL``@~Zc5<1;[IdO1fkgIgE|axfwK\\FhU\\o@x94|I])O#|a^B|O8uoP%ydbN+/=S^anp1^mc5oL,|.qr<S9Fe!]j:[;\'dbOIX\"t`HjgS$0+?/\'\\|.R_C!M<^c=kCGVUa(\"p..W8LCmyE>P+!7TX7!}\\Rv#<2cCBCJC}lm7@Cz4opQ?3s|C1mV}6DO \\$e2nmg1(/ylBk{kH?~a_mWovC2!Zw|oao<q)jx:+2t~N|-\\$^oB.g@F!gcni&`_u4W4iHy6uQ0o;ne:SLWd_ gX($L:XxjWs F-E||x\'!Z9v/#BV+W/[l{_xY8s$5q s1Z=mz|RrY4[nD/AOH}!U1>=Mw\\R=|uQZ4;]0TKw}qXnqnZ{9;Cz}{\\>e?,)\\a#bbsF/Ju[E|>asNM1IS\"{nD[ErV~S)TB=E+T-K!9GQF`NkNT$3YPNF!p+E2U\'tC&{e.}Z;v#q]WB3.r!>Id:;h$ \\[AZ,!~^wG2*@|cjzX\\j0V(6o/rd,B#bE*\\-mWISng 1vA^K`?)4,IMW`#Rc5b3QfLpn35;*5|a8YL~{!g+tGBD4#j^-DE)T1Q<Gu\'o1csMK!Q)Tf|i|+r&#Q6fKW<OI-[KQMUK&#^<DH]\"}$Q\"F~35RC<pIK#.dbUq;uP5nYSApf@?ZHkqfIN_1&;_\"2ERdbh|hGrlwRwrhO5|fqnsRl?=Vw}ti$/R1{Lb!F5~<s:\'K/.FBlrad<IV|h2H\\>_9mQsq\\)a?9dX\'vr~C#AeSf]3-M3o<q0E@/7f0n8h{N&wa5T=#P2Lnf*xyc{@g\'03&.gU.kfdNnSn]oWm-idR5 orq~HPWhFl uZTg3s2~}p_AdT~>j=>:Y)LZ*d(XMLn:%kl%rO458)g#Y6_$u&-N9kvX\'o1}R\\![/tQ\'8pzq2\"hT(>^_ulJzfs[9AKJum,1e]pCDnHo&e]EBS_rdsHm+xJ3uq+&s}=IZm?pa#Nqbda;[HAvh?gT4,Xh!]>`oT}y!gXRkD1.`{N}wTzy>Tx&su1K=6\'HM0|Pa_iir@$N<D#o7M gc2C.vVP(&BC^`(c5PUNMP!r/)l][;<v(HM9\\>=C_3(XS}aT2bDLB}_HU#*CbYC4fC+?*w+GBc/SoGkS_`]3Z92_)l/-wxY+>J0@@*/.;-Y;~,OMFu)aZx&|DGn1g\\I@&Y7~ZFuBF<qreF\".42G\"5$*KmrQ)z<0M_i=L0f-0L<{9cfFSold_qAw-l6(\'<\\jZ@nd9]#Q<~fB/hH,\'uu~m]7KLn)_%;M(ua{1Qt@7C_Yn?,B8jU{Bt7Vk;k:dXI3kv[^~[3#;HT)SX`\'%1qBr7z[_X0L7vm~6?|6^R5AXnK;pI`C gT<?jQ2sXm\'zefl&{ALy1zikawiyJN}nKm+pWzh$!M%?VAQ.`%56^?9q^QoY231=rPW$Er.QT5>{7QXo\\t:I%,tHrUiI?Q|46M;}>.5-5}TusF+&Ymb`yM>Hle246Xy=BeNyU]E(nyScTIDI623.~FK;#w\"#q(Wels(aLu\".!n0*Gh+@,#*w&wNaNzYGLF&vf2$Ev[jT1%~3v!aIn!E*\"Q?mEXqUf[m4.wa.]1\'<P/Sbs#=/=g<^uVT#Pe\"n`(\'eYK#Dlzz9QjMr/O%Man?LO^}Z;@ ?x|sg,\\3&\"gVV,N[:s>a8IWvA\\U79Qj(uZJ<;W1=&A~1MmgS9~-H^[4zQ|CX3<#;I:o|/Mm@w(d|NZapT\\2:fvHy\\|/0j3__02R\'\"+F|(Z`(/kv9{DqQ^\'cw1 !\"_e?.-w\"uCpSf&m*e-mZ\\)5PEK2\\;I2H~%uQZW E|_8Nu1M:]nBO)/_#NJ%7\\Y$O:~]SK)9y{Q5S|2%EAm&<hApclDb4)oPnC,\'/TJIS;7{-Z z*dRa]S.9G6,Peof^.2,m4dafY{HDWr%\"QP9N}uuNL^gvJjF7A!CU,8pkdRG!;@%RwP*wd\'\"ga,@L*Y=f5~8iBMI-up?|D=JbfHze9_N10fn|0nO97[@P]\\m4*4{\"6o|LJWO$O;$BD3\\@l4Vhx:*JU7\\L0>*3I.$Cs\\#nQv[u)^.xf9~tX+n$T?b&-!O_\"HR6R=E,bz)`TKY^eY\"cuS_@Ol%QO26[*lB<PFh<g|u@pi?\\0hrA #ZphA0;NWj-HL|1~tYm]_^J4Md~:0DX9^[~o&|@\'Wm]w_PJ1lAJ1MLNXJBo&$$bQ0w&5\"}+z-,5 $`_(v?h-dK#aPe!qJJS)q<\"/01NHqUfEF9Nb!-i,9/,kFil,r`O5+!a-!~z!Xzk@CO\\)?\"bGPZ-eo!SAb-~M0RJP!hv,I2%n)D2R8WnyD@)^[Bn31Y^9af-[lbGI0WybZ^gobFPr(d%UA\\g;Aec5*:wise61}`|#&ro83~37k}&[10Kz+HF_YUZ?_ t\'NC.dKXP\'b`*_Ag/OZVo!{A^I%rf.$ROP61%W=P$F>YB8|t$D2c?Wg{nM>Le?f\\):n+y32W_9; oZx3^y~3=XmqAUE6P(Qv.4` /{{FPK;F)M)D^=_djn@R@6P~QQGC=?cW!p3({Q!_{sK~|=:*D?!xmsD;\"VE5U$(9\\1;bL$bd@QC:T8D&k>p>b19.KqP5GvBrP=]MNq}2x)QOh LZb>sEL51k&F3V[8kpd={UUu-}A!qyqEkM%lK7A)Qf5vB{On9$/)%lLcGaRcZeM/:bZ !\'&E>QMA%l(F&fQ3pi 2d87+<$A.CJ_SBk^vpV$JJFH4dmVI!R>{&,wW#[}?,s$(+2/~fl4G<Nma-\"&_M>>TI2N:*;V4lkATSE7Gh/31[$S\\qN)joecFkI5}]d:fq\\x{((R`B#BY=+t6BA(g,k4ACVy$q f_FxJRtD)FWG6?.#ZD S@pj~3EF=>J!Z\"{rsKVIE(rk5{&_z{d25?tZn{\'fO&66Gre5YEEBrQz2Xl<umjxse/]Br:6hLQ/ ?pr\\`?vH!5rxBrZdF{0<QiQ>FkBsxN4yAU!(50;7&5Z0a).[ww@ALfxnv)*nnfy/<#XRCURd8zZ\"r3~dxG<!&MF1sd|gHfGdCgW1mj\"(]mfE`-{vM7RPz;yc|<ttLD1w\\67[/dEO#0Vc:/Z}h&jEB[zL/J\'{7*YB?oUHJypq{s*!%dHTN|Yl?{r0O~.;Qw8e#kb2V+$h I&dS)xepi(m4IHQr@L1P+^m67hH6teJaJ6wvtJ|`6t`PBzKryLe08KBOm-?<EoL83&{iBc4ioTcz[E~5d<M&9JAy>NyT(4?>JYv*fp\"+}FxffZtau%zXX>D&Q`}}5h` m:+YvXpEni_^Hn6Xf0w%wBK&EZZ)*4o*UQ4Ps:\"P&*)BAy)(E0O +\'\\0Vt@(eDfDg:r6WXdld8UC`S@nT.=\\>\\7T@O;\\Fvd()6(8bHz(6S}4\\7~izqGhaE!5|vp2|?9lC9&p3)A`-H>b-%D;C;^Yo?_0?rND3ojgAx^R}elz=vr!BMuwcP_]XShAmH^8<df::si<NyR!WK88>dU-z=#*9bh+5\'Pc\\l6]qmwSNuYV;3.+:aebDE,v}``!<UqeJk4\\T%M%?8.;~M;mxR-ZhRG3ii%lVT?94d/l1rDx;&485hz-AWemAs^EXpmfmQ{>6[S7G.LNpbi9p.f!MtM<wa?/Xyb)[ej%!f7}g=Jg3l /KE;+jPd@w#tbYNHc&]j;<A2-\\v85n>=u4AO%:\"Ysgr#a%XlyF\\f/&mnn` `uXcZLPw0fmu_ifV9YyKy3t9%`~ J{@L<8#6Nw{:f?s\'rrJP`k:t\\DOz%>qp>09|I1hZbsy)MXR;if{$G=9TFHegl/|!6k!l[F2X7^cO!L%holQ>;= 6V vu=smuX,>5x5Qf&_l5mv&>wx/~6w+CAB]DnDf;/+,+_Xz &jIy*eMn^W\'#cq%1KP{Y780\'A-rS38qjO.^bV{/o}}z0ju8X.xGE{x:t@\\rrejA{xpR;,dT30F$Fkx\"STS6V~lL~TD:9-2r-qi_FWCvY{W%F\"^P?}=85@\'DNHSru\\%xg=R2Cc`(Z&,,h9w$A[;AdoaNHx#rkmi/ZifZ+5g}My=Wn4,AaaqGz&xMy713aj$?bX_oupMt[_@BZ}o$&%_x[/|6^{_[\"]}H4&C><-* \'9|fjb*HU:%E_GKt5VT(*o%~&ei=k`n%[&|Z1<7l!*A{;He+Wu{T^o6a_%$@punR^KVt9FV5So=H[5<hfy<mW\\H$ZX_pnd9/yL ,7D)[OJ>F:uRkL=H@,CYaW~os0@lvZ+!PH/\']9i+^-V?bS86U{Y%YP{;0[XY$c)&(U!AB~gb\'2VLBb`T:(+e(xAtQX4W}I}jj8J1FMuktuT%sE$_@EwaV AWw%ZQ\'*;1f^_M<0+kP&fi$2T9vOom3\"y#[,$mk0Tk\"mvRcldE{:c6iN@oXOv}S,h+B0HLg| #7A~9#}+jklV++qOR![wNW~BhZ(mtOr.9Ht6Hw}qcl0qC0<B5}.l nG}jQ1]ZGoae6n1Hha~C<k\"BW0X~#4-N\\*D`Mx}#\'il{qLs3_B}gn2tk)>^GQ|ksn*br[$qsq[75K5S0!zfTgvHkK7?JGK-xCad%BmWAWp/C^T*\"JlH7U3er4]~qeURZKaJ&|0r8`=7El:~J\'n\"!{443og\"R\'y{I^?S>T\\p81/u}Y7g`j9*0kdRGH>T`&RN@{>@qYIeo^t%ju_4KB!p>>X\"!t/HDA:#E>O@bvpCX+j _H_6bMOE#6Muu.m+hU6yq-5y~$&1]KO/2I}}NU0tDgT8mwGQ!@[)VdP.3,}xRDK#Bk?Ur8|B Lo@y-/8.S8wEcoMarC<Ronen)(2mPSH)_g&;zf#c-!VT+S%t[=)9MeZpx5cCX[N=sY;L#R_=),ue~y!S%*utC+67N|brP;d)@,NYC0Ajz x-.[)[lOJQ)A^<M`&0!U*DO.J>?$QLN{SaOAr2vU5C/i1Rln2OUF\'16m\"x/HugmewP;T,nWN\'z=~>#U99t&hDU3j5Fe3^y4.k*a(]8_Jh%Lby,B${@+eUZ3aD&NEt9*sPw;Osf:A8{,#+FZ8u/)xjTi@#@#8(C9*OGw+xdShR9kJZzp)J522+AxO 3l-rry!@k{[#cAQs{\'`6M(4U0(s&6BxB_{3/E?MA&(,?xX3C\\!ut6:p.swui{U~Ov7&bBNTwjaWoW$zg:5O!OyWFs*V(j:^Yil \"UC6OSsuU~?T|tVV4J\\Ml!Ri!,=oFpuaa8+L.Uho_&XwAu{{otO_ lYf06l^3Q%elmiJXislC.DmoZ=8:J0v&E.\"&YH$Tk@J5;ZU\"rH[Oj@FQy7yhJnI=ie<6Y.EZau*^@//w!8\\IyjE|}9A9~&PSxN|bZH.*O`^5?G\"m~U1`]qx^,Uar$pWU(i&.,)>Xq`SuC+9+5c,Org8ENjh8N6{Ng9iFIE.Tlp`_^<v0{oQGoS&#V7j\"/gbW{^<Oqu+(0=q#RRcYm2euVX9)S[;u_+F>*>L_Jpa+WxSs-Lj5>$ux+x\\\\q8)o]2,&`.%!ih^[?n5pMj1p6h5;eEXvj/4bZ&IF(pGWcU-P.^dm yBxFTLH![h7%B1Q,G:TOW\"~N(jXy72B;{tgyd|y9j)$+/k rK(qi?:(onZXVW)}ol88U&1.Y8P\\oW.hT<>Uz].8Bn.l;5|9Wjf?pTFxqDX_fuBbSu_S\"Pn,SIc3QvgT8vT(lU=[GAz|Ocd21*e=#pXyw7<>L+w7) u<?_FM3vqO-yDp5th:*H\"\\PgZTRp#{a>|=[\\{Gj1yR*UZGC|qY\\`N;im,K.6y6L?#\\X[[XVda0R!L1}#ew%-GgdX_$lm3exNJWCQR\"l*mXvsyn#<-S\'S!.b>Jle^Y;V7uP3{Xp\\$Fa2Jl32)OXamWg:<q?&j9$*Cg<:7Y7;R|DLu9K4!w/U32Rti_G^cRBYKpT\"ih3! i~Q(0~!\\fd_#|&FEPpe0t^ OMv;4<`-oBXE^<mKS9E(AI!HXCb8[-#(`cnk1y>63Lvn+X{<D6==v\'-o=N#@::7wLeh(c@Pvjc?}%g(CHvV|h|y@/`=l&nj`T:RC<\\F\"cuAQ OPdJz&3FN4\"a4a5VEN1&37xa=-Y\"6|&R5\\OP>b%vu3_$Y/V%-GcCy+9CT7Ds9Y}ty<v\"TE>Zk1X$A]\"WKq/]}B2~TS5V20.B?+AXbBS#EA;}J`y|*qM)UrjD_:~F_ & Gd]]Xqr\'+Na|I~0Q\\(\"sH@7Q!<=2S@dc%lAfkph](IRS5tWbHI@[V4_=zj=`>L0hP>G]<2\\`!NSX mZ$+ECz~kevb_vDg;cjTO?U-\\$/rJ3pDEyA!E_,+*HNd:!:mO]ycf\\.$\"@^wf8mwy\"47M`_~A%oum\'fCXyrYag[]k\\TZgpuB}st.5%H}Tji`y4^V\"w@\',}q1`T/XpXu|0<:,^1!\"a8hK}y4D)X|X/Iwzq({{C(*j!]l(btDl0vqKW=(od=zr}3~/1v~/m(?libqvC<8^rQst^MJYi^+j#y+W~3(8(+ t;v1e<ir|x_Osnw8Hy4C $7(yNP#,*#9J4#A>n[,A\"U-2.Xg|-LD<WmaBJ!r%\"N";

  short inputLength = sizeof(inputString) / sizeof(char);
  short padding = 16 - (inputLength % 16);
  short vetorSize = inputLength + 4 + 16 + padding;
  unsigned char *texto = (unsigned char *)malloc(vetorSize * sizeof(unsigned char));
  if (texto == NULL)
  {
    // Verifique se a alocação foi bem-sucedida
    printf("Falha na alocação de memória.\n");
    return 1; // Saia do programa com um código de erro
  }

  texto[0] = 0x00;
  texto[1] = 0x00;
  texto[2] = 0x27;
  texto[3] = 0x10;
  for (int i = 4; i < inputLength + 4; i++)
  {
    texto[i] = inputString[i - 1];
  }

  // Qualquer tamanho de chave menor ou igual a 32 bytes
  char key[] = "123456789";

  // Input
  for (int i = 0; i < inputLength + 4; i++)
  {
    printf("%02X ", texto[i]);
  }
  printf("\n");

  aes(&texto, 1, key);

  // Output - cyphertext
  for (int i = 0; i < vetorSize; i++)
  {
    printf("%02X ", texto[i]);
  }
  printf("\n");

  aes(&texto, -1, key);

  // Output - plaintext
  for (int i = 0; i < inputLength + 4; i++)
  {
    printf("%02X ", texto[i]);
  }
  printf("\n");

  return 0;
}
