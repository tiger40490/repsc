"Note on some systems vi is used instead of vim, so this file is ignored.

set nu
set bg=dark

"map the 'v' keystroke to mean 'save file unconditionally', very useful when my files become readonly frequently 
map v :w!

"my experimental feature -- use Ctrl-V (in either Insert or Command mode) to paste from the Windows clipboard. Note Mouse is irrelevant here!
:vmap <C-V> "+p

set mouse=a

:vmap <C-C> "+y
"You can use mouse to select within vim, then Ctrl-C i.e. <C-C> to copy into Windows clipboard


"doesn't work:( Suggested on stackoverflow
map <F3> :%!xxd<CR>

" needed to make vim remember last edit location, but I think file ownerId need to match current userId
if has("autocmd")
  au BufReadPost * if line("'\"") > 1 && line("'\"") <= line("$") | exe "normal! g'\"" | endif
endif
