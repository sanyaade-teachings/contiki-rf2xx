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
badd +598 hal.c
badd +1 ../rf230/hal.c
badd +1 ../rum/hal.c
args hal.c
edit hal.c
set splitbelow splitright
wincmd _ | wincmd |
split
1wincmd k
wincmd w
wincmd _ | wincmd |
vsplit
1wincmd h
wincmd w
set nosplitbelow
set nosplitright
wincmd t
set winheight=1 winwidth=1
exe '1resize ' . ((&lines * 37 + 35) / 71)
exe '2resize ' . ((&lines * 31 + 35) / 71)
exe 'vert 2resize ' . ((&columns * 71 + 71) / 142)
exe '3resize ' . ((&lines * 31 + 35) / 71)
exe 'vert 3resize ' . ((&columns * 70 + 71) / 142)
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
118,119fold
123,125fold
123,125fold
127,129fold
137,141fold
122,142fold
145,146fold
149,171fold
117,172fold
177,179fold
185,187fold
189,191fold
182,194fold
197,202fold
205,207fold
210,210fold
210,211fold
210,211fold
210,211fold
214,218fold
214,218fold
210,218fold
210,218fold
221,226fold
229,231fold
234,235fold
238,242fold
196,242fold
176,242fold
248,249fold
248,249fold
252,254fold
257,259fold
257,259fold
262,266fold
262,266fold
269,270fold
269,270fold
273,277fold
246,277fold
281,284fold
287,289fold
287,289fold
292,294fold
297,301fold
297,301fold
297,301fold
304,305fold
308,312fold
280,312fold
279,312fold
318,326fold
330,336fold
340,341fold
340,341fold
343,346fold
348,351fold
353,356fold
329,359fold
362,369fold
373,374fold
378,379fold
381,388fold
390,397fold
403,415fold
372,416fold
419,428fold
431,438fold
441,451fold
456,458fold
459,464fold
455,468fold
455,468fold
471,478fold
486,493fold
495,502fold
504,509fold
481,514fold
516,523fold
516,524fold
531,538fold
540,547fold
549,558fold
526,563fold
526,563fold
566,571fold
573,577fold
573,577fold
579,584fold
579,584fold
586,590fold
317,591fold
316,591fold
594,602fold
620,623fold
625,628fold
661,666fold
660,666fold
670,675fold
680,685fold
676,686fold
605,689fold
691,695fold
713,720fold
722,729fold
731,744fold
698,749fold
698,749fold
698,749fold
753,755fold
756,762fold
756,762fold
753,762fold
844,846fold
847,852fold
1
normal zc
117
normal zo
118
normal zc
122
normal zo
123
normal zo
123
normal zc
123
normal zc
127
normal zc
137
normal zc
122
normal zc
145
normal zc
149
normal zc
117
normal zc
176
normal zo
177
normal zc
182
normal zo
185
normal zc
189
normal zc
182
normal zc
196
normal zo
197
normal zc
205
normal zc
210
normal zo
210
normal zo
210
normal zo
210
normal zo
210
normal zo
210
normal zo
210
normal zo
210
normal zo
210
normal zo
214
normal zo
214
normal zc
214
normal zo
210
normal zo
210
normal zo
221
normal zc
229
normal zc
234
normal zc
238
normal zc
196
normal zc
176
normal zc
246
normal zo
248
normal zo
248
normal zc
248
normal zo
252
normal zc
257
normal zo
257
normal zc
257
normal zo
262
normal zo
262
normal zc
262
normal zo
269
normal zo
269
normal zc
269
normal zo
273
normal zc
246
normal zc
279
normal zo
280
normal zo
281
normal zc
287
normal zo
287
normal zc
287
normal zo
292
normal zc
297
normal zo
297
normal zo
297
normal zc
297
normal zo
297
normal zo
304
normal zc
308
normal zc
280
normal zc
279
normal zc
316
normal zo
317
normal zo
318
normal zc
329
normal zo
330
normal zc
340
normal zo
340
normal zc
340
normal zc
343
normal zc
348
normal zc
353
normal zc
329
normal zc
362
normal zc
372
normal zo
373
normal zc
378
normal zc
381
normal zc
390
normal zc
403
normal zc
372
normal zc
419
normal zc
431
normal zc
441
normal zc
455
normal zo
455
normal zo
456
normal zc
459
normal zc
455
normal zc
455
normal zc
471
normal zc
481
normal zo
486
normal zc
495
normal zc
504
normal zc
481
normal zc
516
normal zo
516
normal zc
516
normal zc
526
normal zo
526
normal zo
531
normal zc
540
normal zc
549
normal zc
526
normal zc
526
normal zc
566
normal zc
573
normal zo
573
normal zc
573
normal zc
579
normal zo
579
normal zc
579
normal zo
586
normal zc
317
normal zc
316
normal zc
594
normal zo
605
normal zo
620
normal zc
625
normal zc
660
normal zo
661
normal zc
660
normal zc
670
normal zc
676
normal zo
680
normal zc
676
normal zc
605
normal zo
691
normal zc
698
normal zo
698
normal zo
698
normal zo
713
normal zc
722
normal zc
731
normal zc
698
normal zc
698
normal zo
698
normal zo
753
normal zo
753
normal zc
756
normal zo
756
normal zo
756
normal zo
753
normal zc
844
normal zo
847
normal zo
let s:l = 631 - ((0 * winheight(0) + 18) / 37)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
631
normal! 0
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
normal zo
614
normal zc
599
normal zc
549
normal zc
626
normal zc
let s:l = 430 - ((2 * winheight(0) + 15) / 31)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
430
normal! 08l
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
let s:l = 246 - ((2 * winheight(0) + 15) / 31)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
246
normal! 0
wincmd w
exe '1resize ' . ((&lines * 37 + 35) / 71)
exe '2resize ' . ((&lines * 31 + 35) / 71)
exe 'vert 2resize ' . ((&columns * 71 + 71) / 142)
exe '3resize ' . ((&lines * 31 + 35) / 71)
exe 'vert 3resize ' . ((&columns * 70 + 71) / 142)
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
