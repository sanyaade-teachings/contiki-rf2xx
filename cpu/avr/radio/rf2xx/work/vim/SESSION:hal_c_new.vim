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
snoremap  b<BS>
map  a
snoremap % b<BS>%
snoremap ' b<BS>'
map Q gq
xmap S <Plug>VSurround
snoremap U b<BS>U
nmap <silent> \t@ :AlignCtrl mIp1P1=l @:'a,.Align
nmap <silent> \aocom :AlignPush:AlignCtrl g /[*/]\acom:AlignPop
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
noremap √õ :call Ri(expand('<cword>'), 1)
noremap √ù :call Ri(expand('<cWORD>'), 0)
noremap √â :call Ri('', 1)
noremap √© :call Ri('', 0)
noremap … :call Ri('', 1)
noremap € :call Ri(expand('<cword>'), 1)
imap <silent> \x <Plug>Traditional
imap <silent> \c <Plug>Traditionalji
noremap › :call Ri(expand('<cWORD>'), 0)
noremap È :call Ri('', 0)
let &cpo=s:cpo_save
unlet s:cpo_save
set autoindent
set background=dark
set backspace=2
set fileencodings=ucs-bom,utf-8,default
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
badd +776 hal.c
badd +1 ../rf230/hal.c
badd +1 ../rum/hal.c
badd +117 ../rf230bb/halbb.c
badd +0 hal.h
args hal.c
edit hal.c
set splitbelow splitright
wincmd _ | wincmd |
split
wincmd _ | wincmd |
split
2wincmd k
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
exe '1resize ' . ((&lines * 33 + 35) / 71)
exe '2resize ' . ((&lines * 32 + 35) / 71)
exe '3resize ' . ((&lines * 1 + 35) / 71)
exe 'vert 3resize ' . ((&columns * 71 + 71) / 142)
exe '4resize ' . ((&lines * 1 + 35) / 71)
exe 'vert 4resize ' . ((&columns * 70 + 71) / 142)
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
1,46fold
134,135fold
139,142fold
139,143fold
145,147fold
155,159fold
138,160fold
163,164fold
167,189fold
133,190fold
196,198fold
204,206fold
208,210fold
201,213fold
216,221fold
224,226fold
229,229fold
229,230fold
229,230fold
229,230fold
233,237fold
233,237fold
229,237fold
229,237fold
240,245fold
248,250fold
253,254fold
257,261fold
215,261fold
195,261fold
269,270fold
269,270fold
273,275fold
278,280fold
278,280fold
283,287fold
283,287fold
290,291fold
290,291fold
294,298fold
267,298fold
302,305fold
308,310fold
308,310fold
313,315fold
318,322fold
318,322fold
318,322fold
325,326fold
329,333fold
301,333fold
300,333fold
340,348fold
352,358fold
362,363fold
362,363fold
365,368fold
370,373fold
375,378fold
351,381fold
384,391fold
395,396fold
400,401fold
403,410fold
412,419fold
425,437fold
394,438fold
441,450fold
453,460fold
463,473fold
478,480fold
481,486fold
477,490fold
477,490fold
494,501fold
509,516fold
518,525fold
527,532fold
504,537fold
539,546fold
539,547fold
554,561fold
563,570fold
572,581fold
549,586fold
549,586fold
591,596fold
598,602fold
598,602fold
604,609fold
604,609fold
611,615fold
339,617fold
338,617fold
620,628fold
620,628fold
642,646fold
652,655fold
657,660fold
705,713fold
704,713fold
719,724fold
730,735fold
726,736fold
631,739fold
741,745fold
763,770fold
772,779fold
781,794fold
748,799fold
748,799fold
748,799fold
618,799fold
803,805fold
806,812fold
806,812fold
803,812fold
816,864fold
897,899fold
904,921fold
900,921fold
925,928fold
950,953fold
954,956fold
957,959fold
960,965fold
966,977fold
987,1000fold
1
normal zc
133
normal zo
134
normal zc
138
normal zo
139
normal zo
139
normal zo
139
normal zo
145
normal zc
155
normal zc
138
normal zc
163
normal zc
167
normal zo
133
normal zo
195
normal zo
196
normal zc
201
normal zo
204
normal zc
208
normal zo
201
normal zc
215
normal zo
216
normal zc
224
normal zc
229
normal zo
229
normal zo
229
normal zo
229
normal zo
229
normal zo
229
normal zo
229
normal zo
229
normal zo
229
normal zo
233
normal zo
233
normal zc
233
normal zo
229
normal zo
229
normal zo
240
normal zc
248
normal zc
253
normal zc
257
normal zc
215
normal zo
195
normal zo
267
normal zo
269
normal zo
269
normal zc
269
normal zo
273
normal zo
278
normal zo
278
normal zc
278
normal zc
283
normal zo
283
normal zo
283
normal zo
290
normal zo
290
normal zc
290
normal zo
294
normal zo
267
normal zc
300
normal zo
301
normal zo
302
normal zc
308
normal zo
308
normal zc
308
normal zc
313
normal zc
318
normal zo
318
normal zo
318
normal zc
318
normal zo
318
normal zo
325
normal zc
329
normal zc
301
normal zc
300
normal zc
338
normal zo
339
normal zo
340
normal zc
351
normal zo
352
normal zc
362
normal zo
362
normal zc
362
normal zo
365
normal zc
370
normal zc
375
normal zc
351
normal zc
384
normal zc
394
normal zo
395
normal zc
400
normal zc
403
normal zc
412
normal zc
425
normal zc
394
normal zc
441
normal zc
453
normal zc
463
normal zc
477
normal zo
477
normal zo
478
normal zc
481
normal zc
477
normal zc
477
normal zo
494
normal zc
504
normal zo
509
normal zc
518
normal zc
527
normal zc
504
normal zc
539
normal zo
539
normal zc
539
normal zc
549
normal zo
549
normal zo
554
normal zc
563
normal zc
572
normal zc
549
normal zc
549
normal zc
591
normal zc
598
normal zo
598
normal zc
598
normal zc
604
normal zo
604
normal zc
604
normal zc
611
normal zc
339
normal zo
338
normal zc
618
normal zo
620
normal zo
620
normal zc
620
normal zc
631
normal zo
642
normal zc
652
normal zc
657
normal zc
704
normal zo
705
normal zo
704
normal zo
719
normal zc
726
normal zo
730
normal zo
726
normal zo
631
normal zc
741
normal zc
748
normal zo
748
normal zo
748
normal zo
763
normal zc
772
normal zc
781
normal zc
748
normal zc
748
normal zc
748
normal zo
618
normal zc
803
normal zo
803
normal zc
806
normal zo
806
normal zo
806
normal zo
803
normal zc
816
normal zc
897
normal zo
900
normal zo
904
normal zc
900
normal zo
925
normal zo
950
normal zc
954
normal zc
957
normal zc
960
normal zc
966
normal zc
987
normal zc
let s:l = 1 - ((0 * winheight(0) + 16) / 33)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
1
normal! 0
wincmd w
argglobal
edit ../rf230bb/halbb.c
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
1,42fold
63,67fold
134,135fold
139,141fold
138,160fold
168,180fold
162,204fold
206,271fold
273,295fold
298,306fold
309,334fold
337,344fold
347,367fold
370,379fold
382,389fold
392,402fold
406,419fold
422,432fold
435,511fold
514,519fold
529,536fold
538,546fold
522,551fold
553,628fold
690,705fold
708,710fold
731,733fold
734,736fold
737,740fold
741,750fold
758,771fold
1
normal zc
63
normal zc
134
normal zc
138
normal zo
139
normal zc
138
normal zc
162
normal zo
168
normal zc
162
normal zc
206
normal zc
273
normal zc
298
normal zc
309
normal zc
337
normal zc
347
normal zc
370
normal zc
382
normal zc
392
normal zc
406
normal zc
422
normal zc
435
normal zc
514
normal zc
522
normal zo
529
normal zc
538
normal zc
522
normal zc
553
normal zc
690
normal zc
708
normal zo
731
normal zc
734
normal zc
737
normal zc
741
normal zo
758
normal zc
let s:l = 745 - ((23 * winheight(0) + 16) / 32)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
745
normal! 08l
wincmd w
argglobal
edit ../rf230/hal.c
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
1,41fold
60,64fold
136,138fold
140,142fold
144,150fold
152,156fold
131,157fold
160,162fold
165,177fold
159,177fold
188,190fold
180,190fold
193,194fold
197,201fold
193,201fold
159,201fold
204,206fold
209,211fold
214,216fold
219,223fold
230,234fold
203,234fold
237,239fold
243,245fold
248,250fold
253,257fold
264,268fold
236,268fold
271,281fold
284,292fold
295,303fold
270,303fold
307,311fold
317,324fold
306,331fold
334,341fold
345,348fold
350,350fold
352,359fold
344,364fold
367,376fold
379,386fold
389,399fold
404,406fold
408,412fold
403,416fold
270,416fold
129,416fold
442,445fold
447,450fold
481,486fold
490,495fold
496,503fold
496,504fold
510,515fold
525,528fold
525,532fold
535,542fold
518,547fold
518,547fold
550,556fold
565,568fold
570,574fold
576,581fold
560,586fold
589,596fold
604,607fold
604,607fold
609,612fold
609,612fold
614,619fold
599,624fold
549,624fold
626,635fold
1
normal zc
60
normal zc
129
normal zo
131
normal zo
136
normal zc
140
normal zc
144
normal zc
152
normal zc
131
normal zc
159
normal zo
159
normal zo
160
normal zc
165
normal zc
159
normal zc
180
normal zo
188
normal zc
180
normal zc
193
normal zo
193
normal zc
197
normal zc
193
normal zc
159
normal zc
203
normal zo
204
normal zc
209
normal zc
214
normal zc
219
normal zc
230
normal zc
203
normal zc
236
normal zo
237
normal zc
243
normal zc
248
normal zc
253
normal zc
264
normal zc
236
normal zc
270
normal zo
270
normal zo
271
normal zc
284
normal zc
295
normal zc
270
normal zc
306
normal zo
307
normal zc
317
normal zc
306
normal zc
334
normal zc
344
normal zo
345
normal zc
350
normal zc
352
normal zc
344
normal zc
367
normal zc
379
normal zc
389
normal zc
403
normal zo
404
normal zc
408
normal zc
403
normal zc
270
normal zc
129
normal zc
442
normal zc
447
normal zc
481
normal zc
490
normal zc
496
normal zo
496
normal zc
496
normal zo
510
normal zc
518
normal zo
518
normal zo
525
normal zo
525
normal zc
525
normal zc
535
normal zc
518
normal zc
518
normal zo
549
normal zo
550
normal zc
560
normal zo
565
normal zc
570
normal zc
576
normal zc
560
normal zc
589
normal zc
599
normal zo
604
normal zo
604
normal zc
604
normal zc
609
normal zo
609
normal zc
609
normal zc
614
normal zc
599
normal zc
549
normal zc
626
normal zc
let s:l = 42 - ((0 * winheight(0) + 0) / 1)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
42
normal! 0
wincmd w
argglobal
edit ../rum/hal.c
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
1,28fold
33,36fold
63,66fold
78,89fold
76,90fold
75,90fold
97,99fold
92,103fold
91,103fold
105,114fold
117,121fold
127,134fold
116,141fold
143,151fold
154,157fold
159,159fold
161,168fold
153,185fold
187,197fold
199,206fold
208,219fold
223,225fold
227,231fold
222,235fold
104,235fold
73,235fold
254,257fold
259,262fold
284,285fold
289,299fold
289,299fold
304,310fold
323,326fold
323,330fold
332,342fold
312,347fold
312,347fold
349,357fold
364,368fold
370,374fold
376,382fold
359,387fold
389,397fold
404,407fold
409,413fold
415,422fold
399,427fold
348,427fold
428,430fold
431,437fold
608,613fold
615,619fold
622,627fold
629,633fold
607,633fold
1
normal zc
33
normal zc
63
normal zc
73
normal zo
75
normal zo
76
normal zo
78
normal zc
76
normal zo
75
normal zc
91
normal zo
92
normal zo
97
normal zc
92
normal zo
91
normal zc
104
normal zo
105
normal zc
116
normal zo
117
normal zc
127
normal zc
116
normal zc
143
normal zc
153
normal zo
154
normal zc
159
normal zc
161
normal zc
153
normal zc
187
normal zc
199
normal zc
208
normal zc
222
normal zo
223
normal zc
227
normal zc
222
normal zc
104
normal zc
73
normal zc
254
normal zc
259
normal zc
284
normal zc
289
normal zo
289
normal zc
289
normal zo
304
normal zc
312
normal zo
312
normal zo
323
normal zo
323
normal zc
323
normal zo
332
normal zc
312
normal zc
312
normal zo
348
normal zo
349
normal zc
359
normal zo
364
normal zc
370
normal zc
376
normal zc
359
normal zc
389
normal zc
399
normal zo
404
normal zc
409
normal zc
415
normal zc
399
normal zc
348
normal zc
428
normal zc
431
normal zc
607
normal zo
608
normal zc
615
normal zc
622
normal zc
629
normal zc
607
normal zc
let s:l = 1 - ((0 * winheight(0) + 0) / 1)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
1
normal! 0
wincmd w
exe '1resize ' . ((&lines * 33 + 35) / 71)
exe '2resize ' . ((&lines * 32 + 35) / 71)
exe '3resize ' . ((&lines * 1 + 35) / 71)
exe 'vert 3resize ' . ((&columns * 71 + 71) / 142)
exe '4resize ' . ((&lines * 1 + 35) / 71)
exe 'vert 4resize ' . ((&columns * 70 + 71) / 142)
tabedit hal.h
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
let s:l = 950 - ((58 * winheight(0) + 34) / 69)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
950
normal! 018l
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
