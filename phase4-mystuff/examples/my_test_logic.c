
// Declear all types
void _error_0;      // Phase 3 Error
void * _ptr_void, ** _ptr_ptr_void;
void _error_1[1];   // Phase 3 ERROR
char _char, * _ptr_char, ** _ptr_ptr_char;
char _arr_char_10[10], *_arr_ptr_char_10[10];
int _int, *_ptr_int, **_ptr_ptr_int;
int _arr_int_10[10], *_arr_ptr_int_10[10];
long _long, *_ptr_long, **_ptr_ptr_long;
long _arr_long_10[10], *_arr_ptr_long_10[10];

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
    // Testing AND
    _int && _fexpect_ret_void   ; //* E4
    _int && _fexpect_ret_void() ; //* E4
    _int && _error_0            ; // E4
    _int && _ptr_void           ; // E4
    _int && _ptr_ptr_void       ; // E4
    _int && _char               ; // E4
    _int && _ptr_char           ; // E4
    _int && _ptr_ptr_char       ; // E4
    _int && _arr_char_10        ; // E4
    _int && _arr_ptr_char_10    ; // E4
    _int && _int                ; // E4
    _int && _ptr_int            ; // E4
    _int && _ptr_ptr_int        ; // E4
    _int && _arr_int_10         ; // E4
    _int && _arr_ptr_int_10     ; // E4
    _int && _long               ; // E4
    _int && _ptr_long           ; // E4
    _int && _ptr_ptr_long       ; // E4
    _int && _arr_long_10        ; // E4
    _int && _arr_ptr_long_10    ; // E4
    _fexpect_ret_void   && _int ; //* E4
    _fexpect_ret_void() && _int ; //* E4
    _error_0            && _int ; // E4
    _ptr_void           && _int ; // E4
    _ptr_ptr_void       && _int ; // E4
    _char               && _int ; // E4
    _ptr_char           && _int ; // E4
    _ptr_ptr_char       && _int ; // E4
    _arr_char_10        && _int ; // E4
    _arr_ptr_char_10    && _int ; // E4
    _int                && _int ; // E4
    _ptr_int            && _int ; // E4
    _ptr_ptr_int        && _int ; // E4
    _arr_int_10         && _int ; // E4
    _arr_ptr_int_10     && _int ; // E4
    _long               && _int ; // E4
    _ptr_long           && _int ; // E4
    _ptr_ptr_long       && _int ; // E4
    _arr_long_10        && _int ; // E4
    _arr_ptr_long_10    && _int ; // E4
    // Testing OR
    _int || _fexpect_ret_void   ; //* E4
    _int || _fexpect_ret_void() ; //* E4
    _int || _error_0            ; // E4
    _int || _ptr_void           ; // E4
    _int || _ptr_ptr_void       ; // E4
    _int || _char               ; // E4
    _int || _ptr_char           ; // E4
    _int || _ptr_ptr_char       ; // E4
    _int || _arr_char_10        ; // E4
    _int || _arr_ptr_char_10    ; // E4
    _int || _int                ; // E4
    _int || _ptr_int            ; // E4
    _int || _ptr_ptr_int        ; // E4
    _int || _arr_int_10         ; // E4
    _int || _arr_ptr_int_10     ; // E4
    _int || _long               ; // E4
    _int || _ptr_long           ; // E4
    _int || _ptr_ptr_long       ; // E4
    _int || _arr_long_10        ; // E4
    _int || _arr_ptr_long_10    ; // E4
    _fexpect_ret_void   || _int ; //* E4
    _fexpect_ret_void() || _int ; //* E4
    _error_0            || _int ; // E4
    _ptr_void           || _int ; // E4
    _ptr_ptr_void       || _int ; // E4
    _char               || _int ; // E4
    _ptr_char           || _int ; // E4
    _ptr_ptr_char       || _int ; // E4
    _arr_char_10        || _int ; // E4
    _arr_ptr_char_10    || _int ; // E4
    _int                || _int ; // E4
    _ptr_int            || _int ; // E4
    _ptr_ptr_int        || _int ; // E4
    _arr_int_10         || _int ; // E4
    _arr_ptr_int_10     || _int ; // E4
    _long               || _int ; // E4
    _ptr_long           || _int ; // E4
    _ptr_ptr_long       || _int ; // E4
    _arr_long_10        || _int ; // E4
    _arr_ptr_long_10    || _int ; // E4
    // Testing NOT
    !_fexpect_ret_void   ; //* E4
    !_fexpect_ret_void() ; //* E4
    !_error_0            ; // E4
    !_ptr_void           ; // E4
    !_ptr_ptr_void       ; // E4
    !_char               ; // E4
    !_ptr_char           ; // E4
    !_ptr_ptr_char       ; // E4
    !_arr_char_10        ; // E4
    !_arr_ptr_char_10    ; // E4
    !_int                ; // E4
    !_ptr_int            ; // E4
    !_ptr_ptr_int        ; // E4
    !_arr_int_10         ; // E4
    !_arr_ptr_int_10     ; // E4
    !_long               ; // E4
    !_ptr_long           ; // E4
    !_ptr_ptr_long       ; // E4
    !_arr_long_10        ; // E4
    !_arr_ptr_long_10    ; // E4
}
