let SessionLoad = 1
if &cp | set nocp | endif
let s:cpo_save=&cpo
set cpo&vim
inoremap <silent> <S-Tab> =BackwardsSnippet()
imap <F10> =strftime("%c")
imap <F7> :VX
imap <F5> :II
imap <F4> :IIW
imap <F3> :CheckSyntax
imap <F2> :make! %
imap <F1> 
snoremap <silent> 	 i<Right>=TriggerSnippet()
snoremap  b<BS>
map  a
snoremap % b<BS>%
snoremap ' b<BS>'
map Q gq
xmap S <Plug>VSurround
snoremap U b<BS>U
nmap <silent> \aocom :AlignPush:AlignCtrl g /[*/]\acom:AlignPop
nmap <silent> \t@ :AlignCtrl mIp1P1=l @:'a,.Align
snoremap \ b<BS>\
nmap <silent> \cv <Plug>VCSVimDiff
nmap <silent> \cu <Plug>VCSUpdate
nmap <silent> \cU <Plug>VCSUnlock
nmap <silent> \cs <Plug>VCSStatus
nmap <silent> \cr <Plug>VCSReview
nmap <silent> \cq <Plug>VCSRevert
nmap <silent> \cn <Plug>VCSAnnotate
nmap <silent> \cN <Plug>VCSSplitAnnotate
nmap <silent> \cl <Plug>VCSLog
nmap <silent> \cL <Plug>VCSLock
nmap <silent> \ci <Plug>VCSInfo
nmap <silent> \cg <Plug>VCSGotoOriginal
nmap <silent> \cG <Plug>VCSClearAndGotoOriginal
nmap <silent> \cd <Plug>VCSDiff
nmap <silent> \cD <Plug>VCSDelete
nmap <silent> \cc <Plug>VCSCommit
nmap <silent> \ca <Plug>VCSAdd
nmap \sv <Plug>SVNVimDiff
nmap \su <Plug>SVNUpdate
nmap \si <Plug>SVNInfo
nmap \ss <Plug>SVNStatus
nmap \sr <Plug>SVNReview
nmap \sq <Plug>SVNRevert
nmap \sl <Plug>SVNLog
nmap \sg <Plug>SVNGotoOriginal
nmap \sd <Plug>SVNDiff
nmap \sc <Plug>SVNCommit
nmap \sG <Plug>SVNClearAndGotoOriginal
nmap \sn <Plug>SVNAnnotate
nmap \sa <Plug>SVNAdd
map \rwp <Plug>RestoreWinPosn
map \swp <Plug>SaveWinPosn
vmap <silent> \x <Plug>VisualTraditional
vmap <silent> \c <Plug>VisualTraditionalj
nmap <silent> \x <Plug>Traditional
nmap <silent> \c <Plug>Traditionalj
vmap <silent> \Htd :<BS><BS><BS>ma'>\Htd
vmap <silent> \tt :<BS><BS><BS>ma'>\tt
vmap <silent> \tp@ :<BS><BS><BS>ma'>\tp@
vmap <silent> \tsq :<BS><BS><BS>ma'>\tsq
vmap <silent> \tsp :<BS><BS><BS>ma'>\tsp
vmap <silent> \tml :<BS><BS><BS>ma'>\tml
vmap <silent> \tab :<BS><BS><BS>ma'>\tab
vmap <silent> \t@ :<BS><BS><BS>ma'>\t@
vmap <silent> \t? :<BS><BS><BS>ma'>\t?
vmap <silent> \t= :<BS><BS><BS>ma'>\t=
vmap <silent> \t< :<BS><BS><BS>ma'>\t<
vmap <silent> \t; :<BS><BS><BS>ma'>\t;
vmap <silent> \t: :<BS><BS><BS>ma'>\t:
vmap <silent> \ts, :<BS><BS><BS>ma'>\ts,
vmap <silent> \t, :<BS><BS><BS>ma'>\t,
vmap <silent> \t| :<BS><BS><BS>ma'>\t|
vmap <silent> \anum :B s/\(\d\)\s\+\(-\=[.,]\=\d\)/\1@\2/ge:AlignCtrl mp0P0gv:Align [.,@]:'<,'>s/\([-0-9.,]*\)\(\s\+\)\([.,]\)/\2\1\3/ge:'<,'>s/@/ /ge
vmap <silent> \afnc :<BS><BS><BS>ma'>\afnc
vmap <silent> \adef :<BS><BS><BS>ma'>\adef
vmap <silent> \adec :<BS><BS><BS>ma'>\adec
vmap <silent> \ascom :<BS><BS><BS>ma'>\ascom
vmap <silent> \aocom :<BS><BS><BS>ma'>\aocom
vmap <silent> \acom :<BS><BS><BS>ma'>\acom
vmap <silent> \abox :<BS><BS><BS>ma'>\abox
vmap <silent> \a= :<BS><BS><BS>ma'>\a=
vmap <silent> \a< :<BS><BS><BS>ma'>\a<
vmap <silent> \a, :<BS><BS><BS>ma'>\a,
vmap <silent> \a? :<BS><BS><BS>ma'>\a?
vmap <silent> \Tsp :<BS><BS><BS>ma'>\Tsp
vmap <silent> \T@ :<BS><BS><BS>ma'>\T@
vmap <silent> \T= :<BS><BS><BS>ma'>\T=
vmap <silent> \T< :<BS><BS><BS>ma'>\T<
vmap <silent> \T: :<BS><BS><BS>ma'>\T:
vmap <silent> \Ts, :<BS><BS><BS>ma'>\Ts,
vmap <silent> \T, :<BS><BS><BS>ma'>\T,
vmap <silent> \T| :<BS><BS><BS>ma'>\T|
map <silent> \tdW@ :AlignCtrl v ^\s*/[/*]:AlignCtrl mWp1P1=l @:'a,.Align
map <silent> \tW@ :AlignCtrl mWp1P1=l @:'a,.Align
omap <silent> \t@ :AlignCtrl mIp1P1=l @:'a,.Align
omap <silent> \aocom :AlignPush:AlignCtrl g /[*/]\acom:AlignPop
nmap \rx <Plug>Rx
nmap \ri <Plug>Ri
snoremap ^ b<BS>^
snoremap ` b<BS>`
nmap cs <Plug>Csurround
nmap ds <Plug>Dsurround
nmap gx <Plug>NetrwBrowseX
xmap s <Plug>Vsurround
nmap ySS <Plug>YSsurround
nmap ySs <Plug>YSsurround
nmap yss <Plug>Yssurround
nmap yS <Plug>YSurround
nmap ys <Plug>Ysurround
map <F12> :tabnext
map <F11> :tabprevious
snoremap <Left> bi
snoremap <Right> a
snoremap <BS> b<BS>
snoremap <silent> <S-Tab> i<Right>=BackwardsSnippet()
nnoremap <silent> <Plug>NetrwBrowseX :call netrw#NetrwBrowseX(expand("<cWORD>"),0)
nnoremap <silent> <Plug>CVSWatchRemove :CVSWatch remove
nnoremap <silent> <Plug>CVSWatchOn :CVSWatch on
nnoremap <silent> <Plug>CVSWatchOff :CVSWatch off
nnoremap <silent> <Plug>CVSWatchAdd :CVSWatch add
nnoremap <silent> <Plug>CVSWatchers :CVSWatchers
nnoremap <silent> <Plug>CVSUnedit :CVSUnedit
nnoremap <silent> <Plug>CVSEditors :CVSEditors
nnoremap <silent> <Plug>CVSEdit :CVSEdit
nnoremap <silent> <Plug>VCSVimDiff :VCSVimDiff
nnoremap <silent> <Plug>VCSUpdate :VCSUpdate
nnoremap <silent> <Plug>VCSUnlock :VCSUnlock
nnoremap <silent> <Plug>VCSStatus :VCSStatus
nnoremap <silent> <Plug>VCSSplitAnnotate :VCSAnnotate!
nnoremap <silent> <Plug>VCSReview :VCSReview
nnoremap <silent> <Plug>VCSRevert :VCSRevert
nnoremap <silent> <Plug>VCSLog :VCSLog
nnoremap <silent> <Plug>VCSLock :VCSLock
nnoremap <silent> <Plug>VCSInfo :VCSInfo
nnoremap <silent> <Plug>VCSClearAndGotoOriginal :VCSGotoOriginal!
nnoremap <silent> <Plug>VCSGotoOriginal :VCSGotoOriginal
nnoremap <silent> <Plug>VCSDiff :VCSDiff
nnoremap <silent> <Plug>VCSDelete :VCSDelete
nnoremap <silent> <Plug>VCSCommit :VCSCommit
nnoremap <silent> <Plug>VCSAnnotate :VCSAnnotate
nnoremap <silent> <Plug>VCSAdd :VCSAdd
nnoremap <silent> <Plug>SVNCommitDiff :SVNCommitDiff
nnoremap <silent> <Plug>SVNVimDiff :SVNVimDiff
nnoremap <silent> <Plug>SVNUpdate :SVNUpdate
nnoremap <silent> <Plug>SVNUnedit :SVNUnedit
nnoremap <silent> <Plug>SVNInfo :SVNInfo
nnoremap <silent> <Plug>SVNStatus :SVNStatus
nnoremap <silent> <Plug>SVNReview :SVNReview
nnoremap <silent> <Plug>SVNRevert :SVNRevert
nnoremap <silent> <Plug>SVNLog :SVNLog
nnoremap <silent> <Plug>SVNClearAndGotoOriginal :SVNGotoOriginal!
nnoremap <silent> <Plug>SVNGotoOriginal :SVNGotoOriginal
nnoremap <silent> <Plug>SVNDiff :SVNDiff
nnoremap <silent> <Plug>SVNCommit :SVNCommit
nnoremap <silent> <Plug>SVNAnnotate :SVNAnnotate
nnoremap <silent> <Plug>SVNAdd :SVNAdd
nmap <silent> <Plug>RestoreWinPosn :call RestoreWinPosn()
nmap <silent> <Plug>SaveWinPosn :call SaveWinPosn()
noremap <Plug>VisualFirstLine :call EnhancedCommentify('', 'first',				    line("'<"), line("'>"))
noremap <Plug>VisualTraditional :call EnhancedCommentify('', 'guess',				    line("'<"), line("'>"))
noremap <Plug>VisualDeComment :call EnhancedCommentify('', 'decomment',				    line("'<"), line("'>"))
noremap <Plug>VisualComment :call EnhancedCommentify('', 'comment',				    line("'<"), line("'>"))
noremap <Plug>FirstLine :call EnhancedCommentify('', 'first')
noremap <Plug>Traditional :call EnhancedCommentify('', 'guess')
noremap <Plug>DeComment :call EnhancedCommentify('', 'decomment')
noremap <Plug>Comment :call EnhancedCommentify('', 'comment')
nmap <SNR>37_WE <Plug>AlignMapsWrapperEnd
nmap <SNR>37_WS <Plug>AlignMapsWrapperStart
map <F10> A =strftime("%c")
map <F7> :VX
map <F5> :II
map <F4> :IIW
map <F3> :CheckSyntax
map <F2> :make! %
nnoremap <Plug>Rx :call Ri('', 1)
nnoremap <Plug>Ri :call Ri('', 0)
map <F1> 
imap S <Plug>ISurround
imap s <Plug>Isurround
inoremap <silent> 	 =TriggerSnippet()
inoremap <silent> 	 =ShowAvailableSnips()
imap  <Plug>Isurround
inoremap  =GetCloseTag()
noremap Û :call Ri(expand('<cword>'), 1)
noremap Ý :call Ri(expand('<cWORD>'), 0)
noremap É :call Ri('', 1)
noremap é :call Ri('', 0)
imap <silent> \x <Plug>Traditional
imap <silent> \c <Plug>Traditionalji
let &cpo=s:cpo_save
unlet s:cpo_save
set autoindent
set background=dark
set backspace=2
set fileencodings=ucs-bom,utf-8,default,latin1
set helplang=en
set history=50
set hlsearch
set nomodeline
set mouse=a
set ruler
set suffixes=.bak,~,.o,.h,.info,.swp,.obj,.info,.aux,.log,.dvi,.bbl,.out,.o,.lo
set viminfo=!,'20,\"500
let s:so_save = &so | let s:siso_save = &siso | set so=0 siso=0
let v:this_session=expand("<sfile>:p")
silent only
cd ~/uni/ct3p60n/code/contiki-2.x/cpu/avr/radio/rf2xx
if expand('%') == '' && !&modified && line('$') <= 1 && getline(1) == ''
  let s:wipebuf = bufnr('%')
endif
set shortmess=aoO
badd +1665 radio.c
badd +1 ../rf230/radio.c
badd +1 ../rum/radio.c
badd +572 ../rf230bb/rf230bb.c
badd +0 ../rf230bb/rf230bb.h
badd +0 radio.h
args radio.c
edit radio.h
set splitbelow splitright
wincmd _ | wincmd |
split
wincmd _ | wincmd |
split
wincmd _ | wincmd |
split
3wincmd k
wincmd w
wincmd w
wincmd w
wincmd _ | wincmd |
vsplit
1wincmd h
wincmd w
set nosplitbelow
set nosplitright
wincmd t
set winheight=1 winwidth=1
exe '1resize ' . ((&lines * 8 + 35) / 71)
exe '2resize ' . ((&lines * 28 + 35) / 71)
exe '3resize ' . ((&lines * 28 + 35) / 71)
exe '4resize ' . ((&lines * 1 + 35) / 71)
exe 'vert 4resize ' . ((&columns * 71 + 71) / 142)
exe '5resize ' . ((&lines * 1 + 35) / 71)
exe 'vert 5resize ' . ((&columns * 70 + 71) / 142)
argglobal
setlocal keymap=
setlocal noarabic
setlocal autoindent
setlocal nobinary
setlocal bufhidden=
setlocal buflisted
setlocal buftype=
setlocal nocindent
setlocal cinkeys=0{,0},0),:,0#,!^F,o,O,e
setlocal cinoptions=
setlocal cinwords=if,else,while,do,for,switch
setlocal comments=sO:*\ -,mO:*\ \ ,exO:*/,s1:/*,mb:*,ex:*/,://
setlocal commentstring=/*%s*/
setlocal complete=.,w,b,u,t,i
setlocal completefunc=
setlocal nocopyindent
setlocal nocursorcolumn
setlocal nocursorline
setlocal define=
setlocal dictionary=
setlocal nodiff
setlocal equalprg=
setlocal errorformat=
setlocal noexpandtab
if &filetype != 'cpp'
setlocal filetype=cpp
endif
setlocal foldcolumn=0
setlocal foldenable
setlocal foldexpr=0
setlocal foldignore=#
setlocal foldlevel=0
setlocal foldmarker={{{,}}}
setlocal foldmethod=manual
setlocal foldminlines=1
setlocal foldnestmax=20
setlocal foldtext=foldtext()
setlocal formatexpr=
setlocal formatoptions=croql
setlocal formatlistpat=^\\s*\\d\\+[\\]:.)}\\t\ ]\\s*
setlocal grepprg=
setlocal iminsert=0
setlocal imsearch=0
setlocal include=
setlocal includeexpr=
setlocal indentexpr=
setlocal indentkeys=0{,0},:,0#,!^F,o,O,e
setlocal noinfercase
setlocal iskeyword=@,48-57,_,192-255
setlocal keywordprg=
setlocal nolinebreak
setlocal nolisp
setlocal nolist
setlocal makeprg=
setlocal matchpairs=(:),{:},[:]
setlocal nomodeline
setlocal modifiable
setlocal nrformats=octal,hex
setlocal nonumber
set numberwidth=3
setlocal numberwidth=3
setlocal omnifunc=ccomplete#Complete
setlocal path=
setlocal nopreserveindent
setlocal nopreviewwindow
setlocal quoteescape=\\
setlocal noreadonly
setlocal norightleft
setlocal rightleftcmd=search
setlocal noscrollbind
setlocal shiftwidth=8
setlocal noshortname
setlocal nosmartindent
setlocal softtabstop=0
setlocal nospell
setlocal spellcapcheck=[.?!]\\_[\\])'\"\	\ ]\\+
setlocal spellfile=
setlocal spelllang=en
setlocal statusline=
setlocal suffixesadd=
setlocal swapfile
setlocal synmaxcol=3000
if &syntax != 'cpp'
setlocal syntax=cpp
endif
setlocal tabstop=8
setlocal tags=
setlocal textwidth=0
setlocal thesaurus=
setlocal nowinfixheight
setlocal nowinfixwidth
setlocal wrap
setlocal wrapmargin=0
silent! normal! zE
1,43fold
95,97fold
99,101fold
103,108fold
110,114fold
117,119fold
121,127fold
132,140fold
204,213fold
216,225fold
229,235fold
236,252fold
229,252fold
254,259fold
260,264fold
254,264fold
267,271fold
272,279fold
267,279fold
281,287fold
288,302fold
281,302fold
323,328fold
357,359fold
361,363fold
427,430fold
1
normal zc
95
normal zc
99
normal zc
103
normal zc
110
normal zc
117
normal zc
121
normal zc
132
normal zc
204
normal zc
216
normal zc
229
normal zo
229
normal zc
236
normal zc
229
normal zc
254
normal zo
254
normal zc
260
normal zc
254
normal zc
267
normal zo
267
normal zc
272
normal zc
267
normal zc
281
normal zo
281
normal zo
288
normal zc
281
normal zc
323
normal zc
357
normal zc
361
normal zc
427
normal zc
let s:l = 454 - ((0 * winheight(0) + 4) / 8)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
454
normal! 014l
wincmd w
argglobal
edit radio.c
setlocal keymap=
setlocal noarabic
setlocal autoindent
setlocal nobinary
setlocal bufhidden=
setlocal buflisted
setlocal buftype=
setlocal nocindent
setlocal cinkeys=0{,0},0),:,0#,!^F,o,O,e
setlocal cinoptions=
setlocal cinwords=if,else,while,do,for,switch
setlocal comments=sO:*\ -,mO:*\ \ ,exO:*/,s1:/*,mb:*,ex:*/,://
setlocal commentstring=/*%s*/
setlocal complete=.,w,b,u,t,i
setlocal completefunc=
setlocal nocopyindent
setlocal nocursorcolumn
setlocal nocursorline
setlocal define=
setlocal dictionary=
setlocal nodiff
setlocal equalprg=
setlocal errorformat=
setlocal noexpandtab
if &filetype != 'c'
setlocal filetype=c
endif
setlocal foldcolumn=0
setlocal foldenable
setlocal foldexpr=0
setlocal foldignore=#
setlocal foldlevel=0
setlocal foldmarker={{{,}}}
setlocal foldmethod=manual
setlocal foldminlines=1
setlocal foldnestmax=20
setlocal foldtext=foldtext()
setlocal formatexpr=
setlocal formatoptions=croql
setlocal formatlistpat=^\\s*\\d\\+[\\]:.)}\\t\ ]\\s*
setlocal grepprg=
setlocal iminsert=0
setlocal imsearch=0
setlocal include=
setlocal includeexpr=
setlocal indentexpr=
setlocal indentkeys=0{,0},:,0#,!^F,o,O,e
setlocal noinfercase
setlocal iskeyword=@,48-57,_,192-255
setlocal keywordprg=
setlocal nolinebreak
setlocal nolisp
setlocal nolist
setlocal makeprg=
setlocal matchpairs=(:),{:},[:]
setlocal nomodeline
setlocal modifiable
setlocal nrformats=octal,hex
setlocal nonumber
set numberwidth=3
setlocal numberwidth=3
setlocal omnifunc=ccomplete#Complete
setlocal path=
setlocal nopreserveindent
setlocal nopreviewwindow
setlocal quoteescape=\\
setlocal noreadonly
setlocal norightleft
setlocal rightleftcmd=search
setlocal noscrollbind
setlocal shiftwidth=8
setlocal noshortname
setlocal nosmartindent
setlocal softtabstop=0
setlocal nospell
setlocal spellcapcheck=[.?!]\\_[\\])'\"\	\ ]\\+
setlocal spellfile=
setlocal spelllang=en
setlocal statusline=
setlocal suffixesadd=
setlocal swapfile
setlocal synmaxcol=3000
if &syntax != 'c'
setlocal syntax=c
endif
setlocal tabstop=8
setlocal tags=
setlocal textwidth=0
setlocal thesaurus=
setlocal nowinfixheight
setlocal nowinfixwidth
setlocal wrap
setlocal wrapmargin=0
silent! normal! zE
1,44fold
85,91fold
94,99fold
105,112fold
105,112fold
118,122fold
128,134fold
136,139fold
124,149fold
151,153fold
155,157fold
159,161fold
163,165fold
189,230fold
232,237fold
245,246fold
248,253fold
255,256fold
258,268fold
270,273fold
296,303fold
296,305fold
307,308fold
312,324fold
340,370fold
337,370fold
373,381fold
373,381fold
385,393fold
397,416fold
397,416fold
420,439fold
445,453fold
445,453fold
456,462fold
465,469fold
486,496fold
500,510fold
513,548fold
556,568fold
572,576fold
588,595fold
598,600fold
603,605fold
609,642fold
645,649fold
652,660fold
663,667fold
671,678fold
682,687fold
690,698fold
690,698fold
701,705fold
709,716fold
720,728fold
731,740fold
743,748fold
752,761fold
765,770fold
773,785fold
788,798fold
801,826fold
830,834fold
846,861fold
846,861fold
864,887fold
890,899fold
902,916fold
918,919fold
922,944fold
947,955fold
947,955fold
958,960fold
963,968fold
970,972fold
975,979fold
444,985fold
994,1004fold
1007,1028fold
1030,1038fold
1041,1051fold
1053,1061fold
1072,1080fold
993,1086fold
993,1089fold
1095,1153fold
1159,1166fold
1169,1190fold
1193,1199fold
1202,1228fold
1231,1239fold
1242,1323fold
1326,1333fold
1336,1419fold
1158,1419fold
1434,1436fold
1441,1443fold
1445,1447fold
1454,1456fold
1461,1463fold
1467,1472fold
1430,1478fold
1485,1488fold
1490,1493fold
1497,1500fold
1504,1506fold
1510,1515fold
1525,1528fold
1532,1535fold
1541,1544fold
1524,1548fold
1556,1558fold
1564,1565fold
1552,1579fold
1582,1583fold
1586,1598fold
1606,1608fold
1614,1617fold
1610,1619fold
1621,1622fold
1603,1632fold
1603,1632fold
1638,1655fold
1661,1665fold
1668,1673fold
1677,1684fold
1694,1706fold
1710,1712fold
1716,1726fold
1729,1771fold
1729,1771fold
1775,1777fold
1772,1780fold
1783,1800fold
1806,1814fold
1816,1820fold
1836,1865fold
1803,1885fold
1889,1898fold
1901,1908fold
1913,1970fold
1887,1971fold
1974,1980fold
1983,1993fold
1996,2001fold
2004,2025fold
2028,2034fold
2037,2060fold
2063,2066fold
2070,2074fold
2070,2074fold
2069,2074fold
2077,2080fold
2083,2089fold
2104,2107fold
2108,2110fold
2121,2123fold
2128,2130fold
2131,2134fold
2143,2146fold
2148,2153fold
2155,2165fold
2182,2184fold
2186,2188fold
2208,2212fold
2225,2227fold
2231,2232fold
2229,2233fold
2241,2243fold
2265,2273fold
2292,2305fold
2315,2317fold
2543,2555fold
2582,2586fold
2559,2595fold
2599,2601fold
2599,2601fold
2604,2606fold
2604,2606fold
2608,2609fold
2610,2616fold
2618,2619fold
2620,2626fold
1
normal zc
85
normal zc
94
normal zc
105
normal zo
105
normal zc
105
normal zo
118
normal zc
124
normal zo
128
normal zc
136
normal zc
124
normal zc
151
normal zc
155
normal zc
159
normal zc
163
normal zc
189
normal zo
232
normal zc
245
normal zc
248
normal zc
255
normal zc
258
normal zc
270
normal zc
296
normal zo
296
normal zc
296
normal zo
307
normal zc
312
normal zc
337
normal zo
340
normal zc
337
normal zo
373
normal zo
373
normal zc
373
normal zo
385
normal zc
397
normal zo
397
normal zc
397
normal zo
420
normal zc
444
normal zo
445
normal zo
445
normal zc
445
normal zo
456
normal zc
465
normal zc
486
normal zc
500
normal zc
513
normal zc
556
normal zc
572
normal zc
588
normal zc
598
normal zc
603
normal zc
609
normal zc
645
normal zc
652
normal zc
663
normal zc
671
normal zc
682
normal zc
690
normal zo
690
normal zc
690
normal zo
701
normal zc
709
normal zc
720
normal zc
731
normal zc
743
normal zc
752
normal zc
765
normal zc
773
normal zc
788
normal zc
801
normal zc
830
normal zc
846
normal zo
846
normal zc
846
normal zo
864
normal zc
890
normal zc
902
normal zc
918
normal zc
922
normal zc
947
normal zo
947
normal zc
947
normal zo
958
normal zc
963
normal zc
970
normal zc
975
normal zc
444
normal zo
993
normal zo
993
normal zo
994
normal zc
1007
normal zc
1030
normal zc
1041
normal zc
1053
normal zc
1072
normal zc
993
normal zo
993
normal zc
1095
normal zc
1158
normal zo
1159
normal zc
1169
normal zc
1193
normal zc
1202
normal zc
1231
normal zc
1242
normal zc
1326
normal zc
1336
normal zc
1158
normal zo
1430
normal zo
1434
normal zc
1441
normal zc
1445
normal zc
1454
normal zc
1461
normal zc
1467
normal zc
1430
normal zo
1485
normal zo
1490
normal zc
1497
normal zc
1504
normal zc
1510
normal zo
1524
normal zo
1525
normal zc
1532
normal zc
1541
normal zc
1524
normal zc
1552
normal zo
1556
normal zc
1564
normal zo
1552
normal zc
1582
normal zc
1586
normal zc
1603
normal zo
1603
normal zo
1606
normal zc
1610
normal zo
1614
normal zc
1610
normal zo
1621
normal zc
1603
normal zc
1603
normal zo
1638
normal zc
1661
normal zc
1668
normal zc
1677
normal zc
1694
normal zc
1710
normal zc
1716
normal zc
1729
normal zo
1729
normal zc
1729
normal zo
1772
normal zo
1775
normal zo
1772
normal zc
1783
normal zc
1803
normal zo
1806
normal zc
1816
normal zc
1836
normal zc
1803
normal zc
1887
normal zo
1889
normal zc
1901
normal zc
1913
normal zc
1887
normal zc
1974
normal zc
1983
normal zc
1996
normal zc
2004
normal zc
2028
normal zc
2037
normal zc
2063
normal zc
2069
normal zo
2070
normal zo
2070
normal zc
2070
normal zo
2069
normal zo
2077
normal zc
2083
normal zc
2104
normal zc
2108
normal zc
2121
normal zc
2128
normal zc
2131
normal zo
2143
normal zc
2148
normal zc
2155
normal zc
2182
normal zc
2186
normal zc
2208
normal zc
2225
normal zc
2229
normal zo
2231
normal zo
2229
normal zc
2241
normal zc
2265
normal zo
2292
normal zo
2315
normal zc
2543
normal zc
2559
normal zo
2582
normal zo
2559
normal zo
2599
normal zo
2599
normal zc
2599
normal zo
2604
normal zo
2604
normal zc
2604
normal zo
2608
normal zc
2610
normal zc
2618
normal zc
2620
normal zc
let s:l = 2571 - ((39 * winheight(0) + 14) / 28)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
2571
normal! 013l
wincmd w
argglobal
edit ../rf230bb/rf230bb.c
setlocal keymap=
setlocal noarabic
setlocal autoindent
setlocal nobinary
setlocal bufhidden=
setlocal buflisted
setlocal buftype=
setlocal nocindent
setlocal cinkeys=0{,0},0),:,0#,!^F,o,O,e
setlocal cinoptions=
setlocal cinwords=if,else,while,do,for,switch
setlocal comments=sO:*\ -,mO:*\ \ ,exO:*/,s1:/*,mb:*,ex:*/,://
setlocal commentstring=/*%s*/
setlocal complete=.,w,b,u,t,i
setlocal completefunc=
setlocal nocopyindent
setlocal nocursorcolumn
setlocal nocursorline
setlocal define=
setlocal dictionary=
setlocal nodiff
setlocal equalprg=
setlocal errorformat=
setlocal noexpandtab
if &filetype != 'c'
setlocal filetype=c
endif
setlocal foldcolumn=0
setlocal foldenable
setlocal foldexpr=0
setlocal foldignore=#
setlocal foldlevel=0
setlocal foldmarker={{{,}}}
setlocal foldmethod=manual
setlocal foldminlines=1
setlocal foldnestmax=20
setlocal foldtext=foldtext()
setlocal formatexpr=
setlocal formatoptions=croql
setlocal formatlistpat=^\\s*\\d\\+[\\]:.)}\\t\ ]\\s*
setlocal grepprg=
setlocal iminsert=0
setlocal imsearch=0
setlocal include=
setlocal includeexpr=
setlocal indentexpr=
setlocal indentkeys=0{,0},:,0#,!^F,o,O,e
setlocal noinfercase
setlocal iskeyword=@,48-57,_,192-255
setlocal keywordprg=
setlocal nolinebreak
setlocal nolisp
setlocal nolist
setlocal makeprg=
setlocal matchpairs=(:),{:},[:]
setlocal nomodeline
setlocal modifiable
setlocal nrformats=octal,hex
setlocal nonumber
set numberwidth=3
setlocal numberwidth=3
setlocal omnifunc=ccomplete#Complete
setlocal path=
setlocal nopreserveindent
setlocal nopreviewwindow
setlocal quoteescape=\\
setlocal noreadonly
setlocal norightleft
setlocal rightleftcmd=search
setlocal noscrollbind
setlocal shiftwidth=8
setlocal noshortname
setlocal nosmartindent
setlocal softtabstop=0
setlocal nospell
setlocal spellcapcheck=[.?!]\\_[\\])'\"\	\ ]\\+
setlocal spellfile=
setlocal spelllang=en
setlocal statusline=
setlocal suffixesadd=
setlocal swapfile
setlocal synmaxcol=3000
if &syntax != 'c'
setlocal syntax=c
endif
setlocal tabstop=8
setlocal tags=
setlocal textwidth=0
setlocal thesaurus=
setlocal nowinfixheight
setlocal nowinfixwidth
setlocal wrap
setlocal wrapmargin=0
silent! normal! zE
1,32fold
38,59fold
63,70fold
72,74fold
76,78fold
76,78fold
80,82fold
80,82fold
84,86fold
88,92fold
94,109fold
111,118fold
120,127fold
120,127fold
129,136fold
138,147fold
149,151fold
154,167fold
153,167fold
170,186fold
188,200fold
209,250fold
253,255fold
258,263fold
265,275fold
278,280fold
283,288fold
208,288fold
292,305fold
309,313fold
289,313fold
316,333fold
339,350fold
374,403fold
336,413fold
416,428fold
431,439fold
444,446fold
452,475fold
478,504fold
507,517fold
521,530fold
518,530fold
537,538fold
540,541fold
546,546fold
546,550fold
552,554fold
568,569fold
571,576fold
585,586fold
589,711fold
715,781fold
715,781fold
785,805fold
809,834fold
838,850fold
854,858fold
862,868fold
869,870fold
875,908fold
871,908fold
913,916fold
917,921fold
924,956fold
958,961fold
958,962fold
958,962fold
963,995fold
1160,1164fold
1168,1176fold
1165,1176fold
1180,1196fold
1200,1225fold
1229,1238fold
1229,1238fold
1242,1245fold
1
normal zc
38
normal zc
63
normal zc
72
normal zc
76
normal zo
76
normal zc
76
normal zo
80
normal zo
80
normal zc
80
normal zo
84
normal zc
88
normal zc
94
normal zc
111
normal zc
120
normal zo
120
normal zc
120
normal zo
129
normal zc
138
normal zo
149
normal zc
153
normal zo
154
normal zc
153
normal zc
170
normal zc
188
normal zc
208
normal zo
209
normal zc
253
normal zo
258
normal zc
265
normal zc
278
normal zc
283
normal zc
208
normal zo
289
normal zo
292
normal zc
309
normal zc
289
normal zo
316
normal zc
336
normal zo
339
normal zo
374
normal zo
336
normal zc
416
normal zc
431
normal zc
444
normal zc
452
normal zc
478
normal zc
507
normal zc
518
normal zo
521
normal zc
518
normal zo
537
normal zc
540
normal zc
546
normal zo
546
normal zc
546
normal zo
552
normal zc
568
normal zc
571
normal zo
585
normal zo
589
normal zo
715
normal zo
715
normal zc
715
normal zo
785
normal zc
809
normal zc
838
normal zc
854
normal zc
862
normal zc
869
normal zc
871
normal zo
875
normal zc
871
normal zc
913
normal zc
917
normal zc
924
normal zc
958
normal zo
958
normal zo
958
normal zo
958
normal zc
958
normal zo
963
normal zc
1160
normal zc
1165
normal zo
1168
normal zc
1165
normal zo
1180
normal zc
1200
normal zc
1229
normal zo
1229
normal zc
1229
normal zo
1242
normal zc
let s:l = 1153 - ((27 * winheight(0) + 14) / 28)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
1153
normal! 09l
wincmd w
argglobal
edit ../rf230/radio.c
setlocal keymap=
setlocal noarabic
setlocal autoindent
setlocal nobinary
setlocal bufhidden=
setlocal buflisted
setlocal buftype=
setlocal nocindent
setlocal cinkeys=0{,0},0),:,0#,!^F,o,O,e
setlocal cinoptions=
setlocal cinwords=if,else,while,do,for,switch
setlocal comments=sO:*\ -,mO:*\ \ ,exO:*/,s1:/*,mb:*,ex:*/,://
setlocal commentstring=/*%s*/
setlocal complete=.,w,b,u,t,i
setlocal completefunc=
setlocal nocopyindent
setlocal nocursorcolumn
setlocal nocursorline
setlocal define=
setlocal dictionary=
setlocal nodiff
setlocal equalprg=
setlocal errorformat=
setlocal noexpandtab
if &filetype != 'c'
setlocal filetype=c
endif
setlocal foldcolumn=0
setlocal foldenable
setlocal foldexpr=0
setlocal foldignore=#
setlocal foldlevel=0
setlocal foldmarker={{{,}}}
setlocal foldmethod=manual
setlocal foldminlines=1
setlocal foldnestmax=20
setlocal foldtext=foldtext()
setlocal formatexpr=
setlocal formatoptions=croql
setlocal formatlistpat=^\\s*\\d\\+[\\]:.)}\\t\ ]\\s*
setlocal grepprg=
setlocal iminsert=0
setlocal imsearch=0
setlocal include=
setlocal includeexpr=
setlocal indentexpr=
setlocal indentkeys=0{,0},:,0#,!^F,o,O,e
setlocal noinfercase
setlocal iskeyword=@,48-57,_,192-255
setlocal keywordprg=
setlocal nolinebreak
setlocal nolisp
setlocal nolist
setlocal makeprg=
setlocal matchpairs=(:),{:},[:]
setlocal nomodeline
setlocal modifiable
setlocal nrformats=octal,hex
setlocal nonumber
set numberwidth=3
setlocal numberwidth=3
setlocal omnifunc=ccomplete#Complete
setlocal path=
setlocal nopreserveindent
setlocal nopreviewwindow
setlocal quoteescape=\\
setlocal noreadonly
setlocal norightleft
setlocal rightleftcmd=search
setlocal noscrollbind
setlocal shiftwidth=8
setlocal noshortname
setlocal nosmartindent
setlocal softtabstop=0
setlocal nospell
setlocal spellcapcheck=[.?!]\\_[\\])'\"\	\ ]\\+
setlocal spellfile=
setlocal spelllang=en
setlocal statusline=
setlocal suffixesadd=
setlocal swapfile
setlocal synmaxcol=3000
if &syntax != 'c'
setlocal syntax=c
endif
setlocal tabstop=8
setlocal tags=
setlocal textwidth=0
setlocal thesaurus=
setlocal nowinfixheight
setlocal nowinfixwidth
setlocal wrap
setlocal wrapmargin=0
silent! normal! zE
let s:l = 1 - ((0 * winheight(0) + 0) / 1)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
1
normal! 0
wincmd w
argglobal
edit ../rum/radio.c
setlocal keymap=
setlocal noarabic
setlocal autoindent
setlocal nobinary
setlocal bufhidden=
setlocal buflisted
setlocal buftype=
setlocal nocindent
setlocal cinkeys=0{,0},0),:,0#,!^F,o,O,e
setlocal cinoptions=
setlocal cinwords=if,else,while,do,for,switch
setlocal comments=sO:*\ -,mO:*\ \ ,exO:*/,s1:/*,mb:*,ex:*/,://
setlocal commentstring=/*%s*/
setlocal complete=.,w,b,u,t,i
setlocal completefunc=
setlocal nocopyindent
setlocal nocursorcolumn
setlocal nocursorline
setlocal define=
setlocal dictionary=
setlocal nodiff
setlocal equalprg=
setlocal errorformat=
setlocal noexpandtab
if &filetype != 'c'
setlocal filetype=c
endif
setlocal foldcolumn=0
setlocal foldenable
setlocal foldexpr=0
setlocal foldignore=#
setlocal foldlevel=0
setlocal foldmarker={{{,}}}
setlocal foldmethod=manual
setlocal foldminlines=1
setlocal foldnestmax=20
setlocal foldtext=foldtext()
setlocal formatexpr=
setlocal formatoptions=croql
setlocal formatlistpat=^\\s*\\d\\+[\\]:.)}\\t\ ]\\s*
setlocal grepprg=
setlocal iminsert=0
setlocal imsearch=0
setlocal include=
setlocal includeexpr=
setlocal indentexpr=
setlocal indentkeys=0{,0},:,0#,!^F,o,O,e
setlocal noinfercase
setlocal iskeyword=@,48-57,_,192-255
setlocal keywordprg=
setlocal nolinebreak
setlocal nolisp
setlocal nolist
setlocal makeprg=
setlocal matchpairs=(:),{:},[:]
setlocal nomodeline
setlocal modifiable
setlocal nrformats=octal,hex
setlocal nonumber
set numberwidth=3
setlocal numberwidth=3
setlocal omnifunc=ccomplete#Complete
setlocal path=
setlocal nopreserveindent
setlocal nopreviewwindow
setlocal quoteescape=\\
setlocal noreadonly
setlocal norightleft
setlocal rightleftcmd=search
setlocal noscrollbind
setlocal shiftwidth=8
setlocal noshortname
setlocal nosmartindent
setlocal softtabstop=0
setlocal nospell
setlocal spellcapcheck=[.?!]\\_[\\])'\"\	\ ]\\+
setlocal spellfile=
setlocal spelllang=en
setlocal statusline=
setlocal suffixesadd=
setlocal swapfile
setlocal synmaxcol=3000
if &syntax != 'c'
setlocal syntax=c
endif
setlocal tabstop=8
setlocal tags=
setlocal textwidth=0
setlocal thesaurus=
setlocal nowinfixheight
setlocal nowinfixwidth
setlocal wrap
setlocal wrapmargin=0
silent! normal! zE
let s:l = 1 - ((0 * winheight(0) + 0) / 1)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
1
normal! 0
wincmd w
2wincmd w
exe '1resize ' . ((&lines * 8 + 35) / 71)
exe '2resize ' . ((&lines * 28 + 35) / 71)
exe '3resize ' . ((&lines * 28 + 35) / 71)
exe '4resize ' . ((&lines * 1 + 35) / 71)
exe 'vert 4resize ' . ((&columns * 71 + 71) / 142)
exe '5resize ' . ((&lines * 1 + 35) / 71)
exe 'vert 5resize ' . ((&columns * 70 + 71) / 142)
tabedit ../rf230bb/rf230bb.h
set splitbelow splitright
set nosplitbelow
set nosplitright
wincmd t
set winheight=1 winwidth=1
argglobal
setlocal keymap=
setlocal noarabic
setlocal autoindent
setlocal nobinary
setlocal bufhidden=
setlocal buflisted
setlocal buftype=
setlocal nocindent
setlocal cinkeys=0{,0},0),:,0#,!^F,o,O,e
setlocal cinoptions=
setlocal cinwords=if,else,while,do,for,switch
setlocal comments=sO:*\ -,mO:*\ \ ,exO:*/,s1:/*,mb:*,ex:*/,://
setlocal commentstring=/*%s*/
setlocal complete=.,w,b,u,t,i
setlocal completefunc=
setlocal nocopyindent
setlocal nocursorcolumn
setlocal nocursorline
setlocal define=
setlocal dictionary=
setlocal nodiff
setlocal equalprg=
setlocal errorformat=
setlocal noexpandtab
if &filetype != 'cpp'
setlocal filetype=cpp
endif
setlocal foldcolumn=0
setlocal foldenable
setlocal foldexpr=0
setlocal foldignore=#
setlocal foldlevel=0
setlocal foldmarker={{{,}}}
setlocal foldmethod=manual
setlocal foldminlines=1
setlocal foldnestmax=20
setlocal foldtext=foldtext()
setlocal formatexpr=
setlocal formatoptions=croql
setlocal formatlistpat=^\\s*\\d\\+[\\]:.)}\\t\ ]\\s*
setlocal grepprg=
setlocal iminsert=0
setlocal imsearch=0
setlocal include=
setlocal includeexpr=
setlocal indentexpr=
setlocal indentkeys=0{,0},:,0#,!^F,o,O,e
setlocal noinfercase
setlocal iskeyword=@,48-57,_,192-255
setlocal keywordprg=
setlocal nolinebreak
setlocal nolisp
setlocal nolist
setlocal makeprg=
setlocal matchpairs=(:),{:},[:]
setlocal nomodeline
setlocal modifiable
setlocal nrformats=octal,hex
setlocal nonumber
set numberwidth=3
setlocal numberwidth=3
setlocal omnifunc=ccomplete#Complete
setlocal path=
setlocal nopreserveindent
setlocal nopreviewwindow
setlocal quoteescape=\\
setlocal readonly
setlocal norightleft
setlocal rightleftcmd=search
setlocal noscrollbind
setlocal shiftwidth=8
setlocal noshortname
setlocal nosmartindent
setlocal softtabstop=0
setlocal nospell
setlocal spellcapcheck=[.?!]\\_[\\])'\"\	\ ]\\+
setlocal spellfile=
setlocal spelllang=en
setlocal statusline=
setlocal suffixesadd=
setlocal swapfile
setlocal synmaxcol=3000
if &syntax != 'cpp'
setlocal syntax=cpp
endif
setlocal tabstop=8
setlocal tags=
setlocal textwidth=0
setlocal thesaurus=
setlocal nowinfixheight
setlocal nowinfixwidth
setlocal wrap
setlocal wrapmargin=0
silent! normal! zE
let s:l = 198 - ((48 * winheight(0) + 34) / 69)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
198
normal! 0
2wincmd w
tabnext 1
if exists('s:wipebuf')
  silent exe 'bwipe ' . s:wipebuf
endif
unlet! s:wipebuf
set winheight=1 winwidth=20 shortmess=filnxtToO
let s:sx = expand("<sfile>:p:r")."x.vim"
if file_readable(s:sx)
  exe "source " . fnameescape(s:sx)
endif
let &so = s:so_save | let &siso = s:siso_save
doautoall SessionLoadPost
unlet SessionLoad
" vim: set ft=vim :
