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
badd +784 hal.c
badd +1 ../rum/hal.c
args hal.c ../rum/hal.c
edit hal.c
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
1,45fold
47,63fold
71,85fold
140,153fold
155,156fold
160,162fold
160,162fold
164,166fold
164,166fold
164,168fold
164,168fold
164,168fold
159,179fold
182,184fold
187,199fold
202,207fold
210,212fold
219,223fold
159,224fold
158,224fold
158,224fold
317,325fold
328,353fold
327,353fold
327,353fold
355,363fold
366,399fold
365,399fold
401,421fold
424,434fold
438,451fold
436,451fold
454,463fold
477,480fold
477,480fold
482,485fold
482,485fold
496,498fold
526,530fold
534,538fold
466,542fold
545,550fold
554,562fold
564,575fold
553,590fold
553,590fold
552,590fold
593,600fold
593,600fold
592,600fold
604,606fold
604,607fold
608,611fold
613,617fold
619,626fold
603,629fold
602,629fold
602,629fold
602,629fold
602,629fold
631,639fold
643,645fold
647,650fold
647,650fold
647,650fold
652,655fold
652,655fold
657,664fold
642,667fold
641,667fold
669,674fold
669,674fold
676,680fold
681,686fold
688,692fold
688,692fold
688,692fold
688,692fold
687,692fold
694,696fold
702,703fold
697,703fold
694,703fold
694,703fold
706,709fold
710,713fold
721,726fold
715,735fold
743,745fold
740,751fold
771,776fold
771,776fold
1
normal zc
47
normal zc
71
normal zc
140
normal zc
155
normal zc
158
normal zo
158
normal zo
159
normal zo
159
normal zo
160
normal zo
160
normal zc
160
normal zo
164
normal zo
164
normal zo
164
normal zo
164
normal zo
164
normal zo
164
normal zo
164
normal zo
164
normal zo
164
normal zo
159
normal zc
182
normal zc
187
normal zc
202
normal zc
210
normal zc
219
normal zc
159
normal zo
158
normal zc
158
normal zo
317
normal zc
327
normal zo
327
normal zo
328
normal zc
327
normal zo
327
normal zo
355
normal zc
365
normal zo
366
normal zc
365
normal zo
401
normal zc
424
normal zc
436
normal zo
438
normal zc
436
normal zo
454
normal zc
466
normal zo
477
normal zo
477
normal zc
477
normal zo
482
normal zo
482
normal zc
482
normal zo
496
normal zc
526
normal zc
534
normal zc
466
normal zc
545
normal zc
552
normal zo
553
normal zo
553
normal zo
554
normal zc
564
normal zc
553
normal zc
553
normal zc
552
normal zo
592
normal zo
593
normal zo
593
normal zc
593
normal zo
592
normal zo
602
normal zo
602
normal zo
602
normal zo
602
normal zo
603
normal zo
604
normal zo
604
normal zc
604
normal zo
608
normal zc
613
normal zc
619
normal zc
603
normal zc
602
normal zo
602
normal zo
602
normal zo
602
normal zo
631
normal zc
641
normal zo
642
normal zo
643
normal zc
647
normal zo
647
normal zo
647
normal zc
647
normal zc
647
normal zc
652
normal zo
652
normal zc
652
normal zo
657
normal zc
642
normal zc
641
normal zo
669
normal zo
669
normal zc
669
normal zo
676
normal zc
681
normal zc
687
normal zo
688
normal zo
688
normal zo
688
normal zo
688
normal zo
688
normal zo
688
normal zo
688
normal zo
687
normal zo
694
normal zo
694
normal zo
694
normal zo
697
normal zo
702
normal zc
697
normal zo
694
normal zo
694
normal zo
706
normal zc
710
normal zc
715
normal zo
721
normal zc
715
normal zc
740
normal zo
743
normal zo
740
normal zc
771
normal zo
771
normal zc
771
normal zo
let s:l = 226 - ((89 * winheight(0) + 17) / 34)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
226
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
47,62fold
77,90fold
92,94fold
97,99fold
97,102fold
116,141fold
115,141fold
143,151fold
152,185fold
152,185fold
187,197fold
198,206fold
187,206fold
208,219fold
220,235fold
237,244fold
254,257fold
259,262fold
269,272fold
274,282fold
284,286fold
293,298fold
287,300fold
246,302fold
304,310fold
313,321fold
323,330fold
313,347fold
312,347fold
311,347fold
349,357fold
360,362fold
360,362fold
364,368fold
370,374fold
376,384fold
359,387fold
358,387fold
358,387fold
358,387fold
389,397fold
389,397fold
400,402fold
404,407fold
409,413fold
415,422fold
415,424fold
399,427fold
398,427fold
398,427fold
429,430fold
431,437fold
440,441fold
443,444fold
446,448fold
461,463fold
458,469fold
475,480fold
608,613fold
615,619fold
622,627fold
629,633fold
1
normal zc
47
normal zc
77
normal zc
92
normal zc
97
normal zo
97
normal zc
97
normal zc
115
normal zo
116
normal zc
115
normal zo
143
normal zc
152
normal zo
152
normal zc
152
normal zo
187
normal zo
187
normal zc
198
normal zc
187
normal zo
208
normal zc
220
normal zc
237
normal zc
246
normal zo
254
normal zc
259
normal zc
269
normal zc
274
normal zc
284
normal zc
287
normal zo
293
normal zc
287
normal zc
246
normal zc
304
normal zc
311
normal zo
312
normal zo
313
normal zo
313
normal zo
323
normal zc
313
normal zo
312
normal zc
311
normal zo
349
normal zc
358
normal zo
358
normal zo
358
normal zo
359
normal zo
360
normal zo
360
normal zc
360
normal zo
364
normal zc
370
normal zc
376
normal zc
359
normal zc
358
normal zo
358
normal zo
358
normal zo
389
normal zo
389
normal zc
389
normal zo
398
normal zo
398
normal zo
399
normal zo
400
normal zc
404
normal zc
409
normal zc
415
normal zo
415
normal zc
415
normal zc
399
normal zc
398
normal zo
398
normal zo
429
normal zc
431
normal zc
440
normal zc
443
normal zc
446
normal zo
458
normal zo
461
normal zo
458
normal zc
475
normal zc
608
normal zc
615
normal zc
622
normal zc
629
normal zc
let s:l = 237 - ((51 * winheight(0) + 17) / 34)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
237
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
