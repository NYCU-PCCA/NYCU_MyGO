se nu et cin sw=4 sts=4 bs=2 so=5 ls=2 cul sc hls is ic
syn on | colo elflord | filetype indent on " scs
map ; :
map <C-l> :nohl<CR>
map <F8> <ESC>:!~/t.sh '%'<CR>
au filetype c,cpp ino <F9> <ESC>:w<CR>:!~/r.sh '%'<CR>
au filetype c,cpp  no <F9> <ESC>:w<CR>:!~/r.sh '%'<CR>
ca Hash w !cpp -dD -P -fpreprocessed \| tr -d '[:space:]' \| md5sum \| cut -c-6
" setxkbmap -option caps:ctrl_modifier
