let SessionLoad = 1
if &cp | set nocp | endif
let s:cpo_save=&cpo
set cpo&vim
inoremap <silent> <S-Tab> =BackwardsSnippet()
imap <F10> =strftime("%c")
imap <F5> :II
imap <F4> :IIW
imap <F3> :CheckSyntax
imap <F2> :make! %
imap <F1> 
snoremap <silent> 	 i<Right>=TriggerSnippet()
vmap  :call Toggle()
nmap  :call Toggle()
snoremap  b<BS>
map  a
snoremap % b<BS>%
snoremap ' b<BS>'
map Q gq
snoremap U b<BS>U
nmap <silent> \t@ :AlignCtrl mIp1P1=l @:'a,.Align
nmap <silent> \aocom :AlignPush:AlignCtrl g /[*/]\acom:AlignPop
snoremap \ b<BS>\
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
nmap \cwr <Plug>CVSWatchRemove
nmap \cwf <Plug>CVSWatchOff
nmap \cwn <Plug>CVSWatchOn
nmap \cwa <Plug>CVSWatchAdd
nmap \cwv <Plug>CVSWatchers
nmap \cv <Plug>CVSVimDiff
nmap \cu <Plug>CVSUpdate
nmap \ct <Plug>CVSUnedit
nmap \cs <Plug>CVSStatus
nmap \cr <Plug>CVSReview
nmap \cq <Plug>CVSRevert
nmap \cl <Plug>CVSLog
nmap \cg <Plug>CVSGotoOriginal
nmap \ci <Plug>CVSEditors
nmap \ce <Plug>CVSEdit
nmap \cd <Plug>CVSDiff
nmap \cc <Plug>CVSCommit
nmap \cG <Plug>CVSClearAndGotoOriginal
nmap \cn <Plug>CVSAnnotate
nmap \ca <Plug>CVSAdd
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
nmap gx <Plug>NetrwBrowseX
snoremap <Left> bi
snoremap <Right> a
snoremap <BS> b<BS>
snoremap <silent> <S-Tab> i<Right>=BackwardsSnippet()
nnoremap <silent> <Plug>NetrwBrowseX :call netrw#NetrwBrowseX(expand("<cWORD>"),0)
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
nnoremap <silent> <Plug>CVSWatchRemove :CVSWatchRemove
nnoremap <silent> <Plug>CVSWatchOff :CVSWatchOff
nnoremap <silent> <Plug>CVSWatchOn :CVSWatchOn
nnoremap <silent> <Plug>CVSWatchAdd :CVSWatchAdd
nnoremap <silent> <Plug>CVSWatchers :CVSWatchers
nnoremap <silent> <Plug>CVSVimDiff :CVSVimDiff
nnoremap <silent> <Plug>CVSUpdate :CVSUpdate
nnoremap <silent> <Plug>CVSUnedit :CVSUnedit
nnoremap <silent> <Plug>CVSStatus :CVSStatus
nnoremap <silent> <Plug>CVSReview :CVSReview
nnoremap <silent> <Plug>CVSRevert :CVSRevert
nnoremap <silent> <Plug>CVSLog :CVSLog
nnoremap <silent> <Plug>CVSClearAndGotoOriginal :CVSGotoOriginal!
nnoremap <silent> <Plug>CVSGotoOriginal :CVSGotoOriginal
nnoremap <silent> <Plug>CVSEditors :CVSEditors
nnoremap <silent> <Plug>CVSEdit :CVSEdit
nnoremap <silent> <Plug>CVSDiff :CVSDiff
nnoremap <silent> <Plug>CVSCommit :CVSCommit
nnoremap <silent> <Plug>CVSAnnotate :CVSAnnotate
nnoremap <silent> <Plug>CVSAdd :CVSAdd
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
map <F5> :II
map <F4> :IIW
map <F3> :CheckSyntax
map <F2> :make! %
nnoremap <Plug>Rx :call Ri('', 1)
nnoremap <Plug>Ri :call Ri('', 0)
map <F1> 
inoremap <silent> 	 =TriggerSnippet()
inoremap <silent> 	 =ShowAvailableSnips()
imap  :call Toggle()
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
badd +1095 radio.c
badd +1 ../rum/radio.c
args radio.c ../rum/radio.c
edit radio.c
set splitbelow splitright
wincmd _ | wincmd |
split
1wincmd k
wincmd w
set nosplitbelow
set nosplitright
wincmd t
set winheight=1 winwidth=1
exe '1resize ' . ((&lines * 34 + 35) / 71)
exe '2resize ' . ((&lines * 34 + 35) / 71)
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
1,40fold
78,79fold
81,82fold
88,92fold
93,106fold
127,131fold
137,139fold
185,188fold
190,193fold
185,193fold
209,211fold
231,240fold
253,261fold
252,261fold
252,261fold
263,266fold
262,270fold
273,275fold
277,281fold
300,303fold
300,303fold
329,331fold
340,343fold
338,343fold
346,348fold
345,348fold
345,348fold
350,359fold
364,367fold
364,367fold
369,375fold
377,378fold
382,387fold
382,389fold
382,389fold
391,394fold
400,404fold
406,409fold
412,421fold
412,421fold
423,439fold
442,445fold
447,450fold
451,454fold
458,461fold
458,461fold
457,461fold
457,461fold
468,470fold
507,515fold
519,531fold
518,532fold
517,532fold
544,551fold
554,556fold
544,556fold
569,571fold
565,574fold
559,574fold
559,574fold
559,574fold
559,574fold
559,574fold
579,582fold
584,586fold
579,586fold
588,595fold
577,598fold
601,608fold
601,608fold
577,608fold
577,608fold
577,608fold
611,621fold
611,621fold
624,632fold
635,637fold
635,637fold
640,658fold
663,665fold
667,669fold
667,669fold
671,679fold
661,681fold
754,795fold
798,800fold
797,800fold
803,808fold
810,820fold
810,820fold
823,840fold
846,857fold
929,934fold
938,940fold
937,958fold
937,958fold
961,966fold
969,992fold
995,997fold
1000,1005fold
1000,1005fold
1007,1010fold
1013,1018fold
1021,1028fold
1030,1039fold
1103,1109fold
1112,1114fold
1112,1114fold
1134,1137fold
1133,1137fold
1140,1147fold
1168,1171fold
1174,1181fold
1206,1210fold
1213,1222fold
1
normal zc
78
normal zc
81
normal zc
88
normal zc
93
normal zc
127
normal zc
137
normal zc
185
normal zo
185
normal zc
190
normal zc
185
normal zo
209
normal zc
231
normal zc
252
normal zo
252
normal zo
253
normal zo
252
normal zc
252
normal zo
262
normal zo
263
normal zc
262
normal zc
273
normal zo
277
normal zc
300
normal zo
300
normal zc
300
normal zo
329
normal zc
338
normal zo
340
normal zo
338
normal zo
345
normal zo
345
normal zo
346
normal zc
345
normal zo
345
normal zo
350
normal zc
364
normal zo
364
normal zc
364
normal zo
369
normal zc
377
normal zc
382
normal zo
382
normal zo
382
normal zo
382
normal zo
382
normal zo
391
normal zc
400
normal zc
406
normal zc
412
normal zo
412
normal zc
412
normal zo
423
normal zc
442
normal zc
447
normal zc
451
normal zc
457
normal zo
457
normal zo
458
normal zo
458
normal zo
458
normal zo
457
normal zc
457
normal zo
468
normal zc
507
normal zc
517
normal zo
518
normal zo
519
normal zc
518
normal zc
517
normal zo
544
normal zo
544
normal zc
554
normal zc
544
normal zc
559
normal zo
559
normal zo
559
normal zo
559
normal zo
559
normal zo
565
normal zo
569
normal zo
565
normal zo
559
normal zo
559
normal zo
559
normal zo
559
normal zo
559
normal zo
577
normal zo
577
normal zo
577
normal zo
577
normal zo
579
normal zo
579
normal zo
584
normal zo
579
normal zo
588
normal zo
577
normal zo
601
normal zo
601
normal zo
601
normal zo
577
normal zo
577
normal zo
577
normal zo
611
normal zo
611
normal zc
611
normal zo
624
normal zc
635
normal zo
635
normal zc
635
normal zo
640
normal zc
661
normal zo
663
normal zc
667
normal zo
667
normal zc
667
normal zc
671
normal zc
661
normal zc
754
normal zc
797
normal zo
798
normal zc
797
normal zo
803
normal zc
810
normal zo
810
normal zc
810
normal zo
823
normal zc
846
normal zc
929
normal zc
937
normal zo
937
normal zo
938
normal zc
937
normal zc
937
normal zo
961
normal zc
969
normal zc
995
normal zc
1000
normal zo
1000
normal zc
1000
normal zo
1007
normal zc
1013
normal zc
1021
normal zc
1030
normal zc
1103
normal zc
1112
normal zo
1112
normal zc
1112
normal zo
1133
normal zo
1134
normal zc
1133
normal zo
1140
normal zc
1168
normal zc
1174
normal zc
1206
normal zc
1213
normal zc
let s:l = 575 - ((2 * winheight(0) + 17) / 34)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
575
normal! 0
wincmd w
argglobal
2argu
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
1,31fold
34,35fold
40,41fold
60,64fold
65,78fold
86,88fold
130,133fold
135,138fold
130,138fold
130,138fold
171,179fold
170,179fold
181,186fold
189,197fold
199,201fold
198,201fold
198,201fold
204,208fold
203,208fold
209,212fold
343,348fold
350,352fold
349,352fold
354,365fold
389,391fold
393,397fold
399,400fold
404,410fold
404,410fold
412,414fold
421,432fold
433,447fold
450,456fold
457,460fold
463,468fold
470,472fold
469,472fold
474,479fold
481,483fold
480,483fold
485,494fold
496,498fold
485,498fold
500,509fold
511,513fold
500,513fold
515,525fold
529,531fold
533,534fold
529,534fold
536,542fold
527,545fold
527,545fold
547,556fold
558,567fold
569,579fold
581,583fold
581,583fold
580,584fold
586,596fold
599,611fold
597,612fold
614,634fold
638,639fold
642,647fold
641,647fold
636,649fold
651,694fold
696,698fold
700,707fold
709,718fold
709,718fold
720,739fold
744,753fold
835,841fold
844,845fold
843,861fold
863,870fold
872,890fold
892,896fold
898,903fold
898,903fold
905,909fold
911,916fold
918,927fold
929,939fold
1009,1016fold
1018,1020fold
1022,1027fold
1029,1036fold
1038,1043fold
1054,1060fold
1062,1069fold
1
normal zc
34
normal zc
40
normal zc
60
normal zc
65
normal zc
86
normal zc
130
normal zo
130
normal zo
130
normal zc
135
normal zc
130
normal zo
130
normal zo
170
normal zo
171
normal zc
170
normal zo
181
normal zc
189
normal zc
198
normal zo
198
normal zo
199
normal zc
198
normal zo
198
normal zo
203
normal zo
204
normal zc
203
normal zo
209
normal zc
343
normal zc
349
normal zo
350
normal zc
349
normal zo
354
normal zc
389
normal zc
393
normal zc
399
normal zc
404
normal zo
404
normal zc
404
normal zo
412
normal zc
421
normal zc
433
normal zc
450
normal zc
457
normal zc
463
normal zc
469
normal zo
470
normal zc
469
normal zo
474
normal zc
480
normal zo
481
normal zc
480
normal zo
485
normal zo
485
normal zc
496
normal zc
485
normal zc
500
normal zo
500
normal zc
511
normal zc
500
normal zc
515
normal zc
527
normal zo
527
normal zo
529
normal zo
529
normal zc
533
normal zc
529
normal zc
536
normal zc
527
normal zc
527
normal zo
547
normal zc
558
normal zc
569
normal zc
580
normal zo
581
normal zo
581
normal zc
581
normal zo
580
normal zo
586
normal zc
597
normal zo
599
normal zc
597
normal zc
614
normal zc
636
normal zo
638
normal zc
641
normal zo
642
normal zc
641
normal zc
636
normal zc
651
normal zc
696
normal zc
700
normal zc
709
normal zo
709
normal zc
709
normal zo
720
normal zc
744
normal zc
835
normal zc
843
normal zo
844
normal zc
843
normal zc
863
normal zc
872
normal zc
892
normal zc
898
normal zo
898
normal zc
898
normal zo
905
normal zc
911
normal zc
918
normal zc
929
normal zc
1009
normal zc
1018
normal zc
1022
normal zc
1029
normal zc
1038
normal zc
1054
normal zc
1062
normal zc
let s:l = 527 - ((46 * winheight(0) + 17) / 34)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
527
normal! 0
wincmd w
exe '1resize ' . ((&lines * 34 + 35) / 71)
exe '2resize ' . ((&lines * 34 + 35) / 71)
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
