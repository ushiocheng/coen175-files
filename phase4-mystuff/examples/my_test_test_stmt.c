
// Declear all types
void _error_0;      // Phase 3 Error
void * _ptr_void, ** _ptr_ptr_void;
void _error_1[1];   // Phase 3 ERROR
char _char, * _ptr_char, ** _ptr_ptr_char;
char _arr_char_10[10], *_ptr_arr_char_10[10];
int _int, *_ptr_int, **_ptr_ptr_int;
int _arr_int_10[10], *_ptr_arr_int_10[10];
long _long, *_ptr_long, **_ptr_ptr_long;
long _arr_long_10[10], *_ptr_arr_long_10[10];

void _fexpect_void          (void)      {}
void _fexpect_ptr_void      (void* a)   {}
void _fexpect_char          (char a)    {}
void _fexpect_ptr_char      (char* a)   {}
void _fexpect_ptr_ptr_char  (char** a)  {}
void _fexpect_int           (int  a)    {}
void _fexpect_ptr_int       (int * a)   {}
void _fexpect_ptr_ptr_int   (int ** a)  {}
void _fexpect_long          (long a)    {}
void _fexpect_ptr_long      (long* a)   {}
void _fexpect_ptr_ptr_long  (long** a)  {}

void    _fexpect_ret_void();
void*   _fexpect_ret_ptr_void();
void**  _fexpect_ret_ptr_ptr_void();
char    _fexpect_ret_char();
char*   _fexpect_ret_ptr_char();
char**  _fexpect_ret_ptr_ptr_char();
int     _fexpect_ret_int ();
int *   _fexpect_ret_ptr_int ();
int **  _fexpect_ret_ptr_ptr_int ();
long    _fexpect_ret_long();
long*   _fexpect_ret_ptr_long();
long**  _fexpect_ret_ptr_ptr_long();

// testing return
void    _fexpect_ret_void(void){}
void*   _fexpect_ret_ptr_void(void){}
void**  _fexpect_ret_ptr_ptr_void(void){}
char    _fexpect_ret_char(void){}
char*   _fexpect_ret_ptr_char(void){}
char**  _fexpect_ret_ptr_ptr_char(void){}
int     _fexpect_ret_int (void){}
int *   _fexpect_ret_ptr_int (void){}
int **  _fexpect_ret_ptr_ptr_int (void){}
long    _fexpect_ret_long(void){}
long*   _fexpect_ret_ptr_long(void){}
long**  _fexpect_ret_ptr_ptr_long(void){}

int main(void) {
    // Testing E2
    if (_fexpect_ret_void() ) {} //* E2
    if (_error_0            ) {} // E2
    if (_ptr_void           ) {} // E2
    if (_ptr_ptr_void       ) {} // E2
    if (_char               ) {} // E2
    if (_ptr_char           ) {} // E2
    if (_ptr_ptr_char       ) {} // E2
    if (_arr_char_10        ) {} // E2
    if (_ptr_arr_char_10    ) {} // E2
    if (_int                ) {} // E2
    if (_ptr_int            ) {} // E2
    if (_ptr_ptr_int        ) {} // E2
    if (_arr_int_10         ) {} // E2
    if (_ptr_arr_int_10     ) {} // E2
    if (_long               ) {} // E2
    if (_ptr_long           ) {} // E2
    if (_ptr_ptr_long       ) {} // E2
    if (_arr_long_10        ) {} // E2
    if (_ptr_arr_long_10    ) {} // E2

    while (_fexpect_ret_void() ){} //* E2
    while (_error_0            ){} // E2
    while (_ptr_void           ){} // E2
    while (_ptr_ptr_void       ){} // E2
    while (_char               ){} // E2
    while (_ptr_char           ){} // E2
    while (_ptr_ptr_char       ){} // E2
    while (_arr_char_10        ){} // E2
    while (_ptr_arr_char_10    ){} // E2
    while (_int                ){} // E2
    while (_ptr_int            ){} // E2
    while (_ptr_ptr_int        ){} // E2
    while (_arr_int_10         ){} // E2
    while (_ptr_arr_int_10     ){} // E2
    while (_long               ){} // E2
    while (_ptr_long           ){} // E2
    while (_ptr_ptr_long       ){} // E2
    while (_arr_long_10        ){} // E2
    while (_ptr_arr_long_10    ){} // E2

    for (_int = 0 ; _fexpect_ret_void() ;_int=_int ) {} //* E2
    for (_int = 0 ; _error_0            ;_int=_int ) {} // E2
    for (_int = 0 ; _ptr_void           ;_int=_int ) {} // E2
    for (_int = 0 ; _ptr_ptr_void       ;_int=_int ) {} // E2
    for (_int = 0 ; _char               ;_int=_int ) {} // E2
    for (_int = 0 ; _ptr_char           ;_int=_int ) {} // E2
    for (_int = 0 ; _ptr_ptr_char       ;_int=_int ) {} // E2
    for (_int = 0 ; _arr_char_10        ;_int=_int ) {} // E2
    for (_int = 0 ; _ptr_arr_char_10    ;_int=_int ) {} // E2
    for (_int = 0 ; _int                ;_int=_int ) {} // E2
    for (_int = 0 ; _ptr_int            ;_int=_int ) {} // E2
    for (_int = 0 ; _ptr_ptr_int        ;_int=_int ) {} // E2
    for (_int = 0 ; _arr_int_10         ;_int=_int ) {} // E2
    for (_int = 0 ; _ptr_arr_int_10     ;_int=_int ) {} // E2
    for (_int = 0 ; _long               ;_int=_int ) {} // E2
    for (_int = 0 ; _ptr_long           ;_int=_int ) {} // E2
    for (_int = 0 ; _ptr_ptr_long       ;_int=_int ) {} // E2
    for (_int = 0 ; _arr_long_10        ;_int=_int ) {} // E2
    for (_int = 0 ; _ptr_arr_long_10    ;_int=_int ) {} // E2
}
