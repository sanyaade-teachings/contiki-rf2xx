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
nmap <silent> \aocom :AlignPush:AlignCtrl g /[*/]\acom:AlignPop
nmap <silent> \t@ :AlignCtrl mIp1P1=l @:'a,.Align
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
badd +394 hal.h
badd +1 ../rum/hal.h
args hal.h ../rum/hal.h
edit hal.h
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
45,56fold
60,68fold
70,87fold
90,98fold
89,98fold
106,109fold
110,116fold
106,116fold
106,116fold
106,116fold
106,117fold
120,132fold
120,132fold
120,132fold
120,144fold
146,159fold
146,159fold
161,169fold
172,176fold
172,176fold
178,184fold
185,187fold
188,190fold
191,193fold
194,196fold
172,203fold
172,203fold
171,203fold
208,210fold
211,220fold
221,230fold
171,230fold
171,230fold
171,230fold
233,237fold
240,244fold
239,244fold
245,251fold
252,254fold
255,257fold
258,260fold
271,273fold
274,289fold
290,299fold
232,301fold
232,301fold
304,308fold
310,318fold
319,321fold
322,324fold
338,340fold
341,350fold
351,360fold
303,360fold
303,360fold
363,367fold
363,367fold
369,375fold
376,378fold
379,381fold
382,384fold
392,394fold
395,402fold
403,412fold
362,412fold
362,412fold
362,412fold
362,412fold
415,435fold
415,436fold
414,436fold
439,443fold
445,451fold
445,451fold
452,454fold
452,454fold
455,457fold
458,460fold
461,463fold
461,463fold
439,475fold
439,475fold
476,478fold
479,488fold
489,496fold
438,496fold
498,500fold
438,500fold
438,501fold
503,507fold
503,507fold
503,507fold
509,514fold
508,514fold
508,514fold
508,514fold
508,514fold
518,520fold
518,520fold
516,520fold
515,520fold
515,520fold
515,520fold
515,520fold
515,520fold
515,520fold
515,520fold
521,523fold
524,526fold
515,533fold
503,533fold
503,533fold
534,536fold
534,536fold
534,536fold
537,546fold
537,546fold
547,567fold
547,567fold
547,567fold
547,570fold
502,570fold
573,576fold
573,577fold
579,585fold
586,588fold
589,591fold
592,594fold
595,596fold
597,599fold
609,616fold
617,626fold
573,626fold
572,626fold
572,626fold
572,627fold
635,641fold
642,644fold
645,647fold
648,650fold
654,668fold
670,678fold
680,710fold
628,710fold
628,710fold
713,717fold
719,725fold
726,728fold
729,731fold
732,734fold
738,740fold
741,757fold
758,784fold
712,784fold
801,807fold
809,836fold
808,837fold
840,843fold
839,844fold
845,851fold
852,858fold
845,858fold
859,871fold
873,878fold
880,883fold
884,887fold
888,891fold
892,895fold
914,919fold
922,930fold
960,966fold
960,966fold
968,973fold
968,973fold
975,976fold
968,976fold
979,984fold
1002,1009fold
999,1009fold
1011,1018fold
1
normal zc
45
normal zc
60
normal zc
70
normal zc
89
normal zo
90
normal zo
89
normal zc
106
normal zo
106
normal zo
106
normal zo
106
normal zo
106
normal zo
110
normal zo
106
normal zo
106
normal zo
106
normal zo
106
normal zc
120
normal zo
120
normal zo
120
normal zo
120
normal zc
120
normal zo
120
normal zo
120
normal zc
146
normal zo
146
normal zc
146
normal zo
161
normal zc
171
normal zo
171
normal zo
171
normal zo
171
normal zo
172
normal zo
172
normal zo
172
normal zo
172
normal zc
172
normal zo
178
normal zc
185
normal zc
188
normal zc
191
normal zc
194
normal zc
172
normal zo
172
normal zo
171
normal zo
208
normal zc
211
normal zc
221
normal zc
171
normal zc
171
normal zc
171
normal zo
232
normal zo
232
normal zo
233
normal zc
239
normal zo
240
normal zo
239
normal zc
245
normal zc
252
normal zc
255
normal zc
258
normal zc
271
normal zc
274
normal zc
290
normal zc
232
normal zc
232
normal zo
303
normal zo
303
normal zo
304
normal zc
310
normal zc
319
normal zc
322
normal zc
338
normal zc
341
normal zc
351
normal zc
303
normal zc
303
normal zo
362
normal zo
362
normal zo
362
normal zo
362
normal zo
363
normal zo
363
normal zc
363
normal zo
369
normal zc
376
normal zc
379
normal zc
382
normal zc
392
normal zc
395
normal zc
403
normal zc
362
normal zc
362
normal zo
362
normal zo
362
normal zo
414
normal zo
415
normal zo
415
normal zo
415
normal zo
414
normal zc
438
normal zo
438
normal zo
438
normal zo
439
normal zo
439
normal zo
439
normal zc
445
normal zo
445
normal zc
445
normal zo
452
normal zo
452
normal zc
452
normal zo
455
normal zc
458
normal zc
461
normal zo
461
normal zc
461
normal zo
439
normal zo
439
normal zo
476
normal zc
479
normal zc
489
normal zc
438
normal zc
498
normal zc
438
normal zc
438
normal zo
502
normal zo
503
normal zo
503
normal zo
503
normal zo
503
normal zo
503
normal zc
503
normal zo
503
normal zo
508
normal zo
508
normal zo
508
normal zo
508
normal zo
509
normal zo
508
normal zc
508
normal zo
508
normal zo
508
normal zo
515
normal zo
515
normal zo
515
normal zo
515
normal zo
515
normal zo
515
normal zo
515
normal zo
515
normal zo
516
normal zo
518
normal zo
518
normal zc
518
normal zo
516
normal zo
515
normal zc
515
normal zo
515
normal zo
515
normal zo
515
normal zo
515
normal zo
515
normal zo
521
normal zc
524
normal zc
515
normal zo
503
normal zo
503
normal zo
534
normal zo
534
normal zo
534
normal zc
534
normal zo
534
normal zo
537
normal zo
537
normal zc
537
normal zo
547
normal zo
547
normal zo
547
normal zo
547
normal zo
547
normal zo
547
normal zo
547
normal zc
502
normal zc
572
normal zo
572
normal zo
572
normal zo
573
normal zo
573
normal zo
573
normal zo
573
normal zo
579
normal zc
586
normal zc
589
normal zc
592
normal zc
595
normal zc
597
normal zc
609
normal zc
617
normal zc
573
normal zc
572
normal zc
572
normal zo
572
normal zo
628
normal zo
628
normal zo
635
normal zc
642
normal zc
645
normal zc
648
normal zc
654
normal zc
670
normal zc
680
normal zc
628
normal zc
628
normal zo
712
normal zo
713
normal zc
719
normal zc
726
normal zc
729
normal zc
732
normal zc
738
normal zc
741
normal zc
758
normal zc
712
normal zc
801
normal zc
808
normal zo
809
normal zc
808
normal zo
839
normal zo
840
normal zc
839
normal zo
845
normal zo
845
normal zc
852
normal zc
845
normal zo
859
normal zo
873
normal zc
880
normal zc
884
normal zc
888
normal zc
892
normal zc
914
normal zc
922
normal zc
960
normal zo
960
normal zc
960
normal zo
968
normal zo
968
normal zo
968
normal zc
968
normal zc
975
normal zo
968
normal zo
979
normal zc
999
normal zo
1002
normal zc
999
normal zc
1011
normal zc
let s:l = 1 - ((0 * winheight(0) + 17) / 34)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
1
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
1,31fold
34,42fold
75,88fold
75,89fold
90,98fold
100,156fold
158,205fold
209,251fold
208,251fold
207,251fold
253,294fold
298,303fold
304,309fold
310,311fold
310,311fold
312,313fold
298,344fold
297,344fold
296,344fold
352,376fold
349,376fold
348,376fold
348,385fold
347,385fold
347,385fold
346,385fold
389,392fold
394,399fold
400,401fold
402,403fold
394,403fold
389,417fold
389,443fold
388,443fold
387,443fold
445,509fold
511,577fold
49,581fold
582,588fold
582,588fold
582,588fold
592,600fold
602,629fold
601,630fold
633,634fold
632,635fold
636,642fold
643,649fold
636,649fold
653,656fold
650,661fold
687,693fold
695,698fold
699,702fold
703,706fold
707,710fold
711,714fold
719,726fold
766,770fold
789,790fold
792,795fold
802,806fold
807,813fold
1
normal zc
34
normal zc
49
normal zo
75
normal zo
75
normal zc
75
normal zo
90
normal zc
100
normal zc
158
normal zc
207
normal zo
208
normal zo
209
normal zo
208
normal zc
207
normal zc
253
normal zc
296
normal zo
297
normal zo
298
normal zo
298
normal zc
304
normal zc
310
normal zo
310
normal zc
310
normal zo
312
normal zc
298
normal zo
297
normal zc
296
normal zc
346
normal zo
347
normal zo
347
normal zo
348
normal zo
348
normal zo
349
normal zo
352
normal zo
349
normal zo
348
normal zo
348
normal zc
347
normal zc
347
normal zo
346
normal zc
387
normal zo
388
normal zo
389
normal zo
389
normal zo
389
normal zc
394
normal zo
394
normal zc
400
normal zc
402
normal zc
394
normal zo
389
normal zo
389
normal zc
388
normal zc
387
normal zc
445
normal zc
511
normal zc
49
normal zo
582
normal zo
582
normal zo
582
normal zc
582
normal zo
582
normal zo
592
normal zc
601
normal zo
602
normal zc
601
normal zo
632
normal zo
633
normal zc
632
normal zo
636
normal zo
636
normal zc
643
normal zc
636
normal zo
650
normal zo
653
normal zo
650
normal zc
687
normal zc
695
normal zc
699
normal zc
703
normal zc
707
normal zc
711
normal zc
719
normal zc
766
normal zc
789
normal zc
792
normal zc
802
normal zc
807
normal zc
let s:l = 835 - ((47 * winheight(0) + 17) / 34)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
835
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
