
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
void    _fexpect_ret_void(void){
    return _error_0;            // E1
    return _ptr_void;           //* E1
    return _ptr_ptr_void;       //* E1
    return _error_1;            // E1
    return _char;               //* E1
    return _ptr_char;           //* E1
    return _ptr_ptr_char;       //* E1
    return _arr_char_10;        //* E1
    return _ptr_arr_char_10;    //* E1
    return _int;                //* E1
    return _ptr_int;            //* E1
    return _ptr_ptr_int;        //* E1
    return _arr_int_10;         //* E1
    return _ptr_arr_int_10;     //* E1
    return _long;               //* E1
    return _ptr_long;           //* E1
    return _ptr_ptr_long;       //* E1
    return _arr_long_10;        //* E1
    return _ptr_arr_long_10;    //* E1
}
void*   _fexpect_ret_ptr_void(void){
    // ptr(void) => ptr(T)
    return _error_0;            // E1
    return _ptr_void;           // E1
    return _ptr_ptr_void;       // E1
    return _error_1;            // E1
    return _char;               //* E1
    return _ptr_char;           // E1
    return _ptr_ptr_char;       // E1
    return _arr_char_10;        // E1
    return _ptr_arr_char_10;    // E1
    return _int;                //* E1
    return _ptr_int;            // E1
    return _ptr_ptr_int;        // E1
    return _arr_int_10;         // E1
    return _ptr_arr_int_10;     // E1
    return _long;               //* E1
    return _ptr_long;           // E1
    return _ptr_ptr_long;       // E1
    return _arr_long_10;        // E1
    return _ptr_arr_long_10;    // E1
}
void**  _fexpect_ret_ptr_ptr_void(void){
    return _error_0;            // E1
    return _ptr_void;           // E1
    return _ptr_ptr_void;       // E1
    return _error_1;            // E1
    return _char;               //* E1
    return _ptr_char;           //* E1
    return _ptr_ptr_char;       //* E1
    return _arr_char_10;        //* E1
    return _ptr_arr_char_10;    //* E1
    return _int;                //* E1
    return _ptr_int;            //* E1
    return _ptr_ptr_int;        //* E1
    return _arr_int_10;         //* E1
    return _ptr_arr_int_10;     //* E1
    return _long;               //* E1
    return _ptr_long;           //* E1
    return _ptr_ptr_long;       //* E1
    return _arr_long_10;        //* E1
    return _ptr_arr_long_10;    //* E1
}
char    _fexpect_ret_char(void){
    return _error_0;            // E1
    return _ptr_void;           //* E1
    return _ptr_ptr_void;       //* E1
    return _error_1;            // E1
    return _char;               // E1
    return _ptr_char;           //* E1
    return _ptr_ptr_char;       //* E1
    return _arr_char_10;        //* E1
    return _ptr_arr_char_10;    //* E1
    return _int;                // E1
    return _ptr_int;            //* E1
    return _ptr_ptr_int;        //* E1
    return _arr_int_10;         //* E1
    return _ptr_arr_int_10;     //* E1
    return _long;               // E1
    return _ptr_long;           //* E1
    return _ptr_ptr_long;       //* E1
    return _arr_long_10;        //* E1
    return _ptr_arr_long_10;    //* E1
}
char*   _fexpect_ret_ptr_char(void){
    return _error_0;            // E1
    return _ptr_void;           // E1
    return _ptr_ptr_void;       //* E1
    return _error_1;            // E1
    return _char;               //* E1
    return _ptr_char;           // E1
    return _ptr_ptr_char;       //* E1
    return _arr_char_10;        // E1
    return _ptr_arr_char_10;    //* E1
    return _int;                //* E1
    return _ptr_int;            //* E1
    return _ptr_ptr_int;        //* E1
    return _arr_int_10;         //* E1
    return _ptr_arr_int_10;     //* E1
    return _long;               //* E1
    return _ptr_long;           //* E1
    return _ptr_ptr_long;       //* E1
    return _arr_long_10;        //* E1
    return _ptr_arr_long_10;    //* E1
}
char**  _fexpect_ret_ptr_ptr_char(void){
    return _error_0;            // E1
    return _ptr_void;           // E1
    return _ptr_ptr_void;       //* E1
    return _error_1;            // E1
    return _char;               //* E1
    return _ptr_char;           //* E1
    return _ptr_ptr_char;       // E1
    return _arr_char_10;        //* E1
    return _ptr_arr_char_10;    // E1
    return _int;                //* E1
    return _ptr_int;            //* E1
    return _ptr_ptr_int;        //* E1
    return _arr_int_10;         //* E1
    return _ptr_arr_int_10;     //* E1
    return _long;               //* E1
    return _ptr_long;           //* E1
    return _ptr_ptr_long;       //* E1
    return _arr_long_10;        //* E1
    return _ptr_arr_long_10;    //* E1
}
int     _fexpect_ret_int (void){
    return _error_0;            // E1
    return _ptr_void;           //* E1
    return _ptr_ptr_void;       //* E1
    return _error_1;            // E1
    return _char;               // E1
    return _ptr_char;           //* E1
    return _ptr_ptr_char;       //* E1
    return _arr_char_10;        //* E1
    return _ptr_arr_char_10;    //* E1
    return _int;                // E1
    return _ptr_int;            //* E1
    return _ptr_ptr_int;        //* E1
    return _arr_int_10;         //* E1
    return _ptr_arr_int_10;     //* E1
    return _long;               // E1
    return _ptr_long;           //* E1
    return _ptr_ptr_long;       //* E1
    return _arr_long_10;        //* E1
    return _ptr_arr_long_10;    //* E1
}
int *   _fexpect_ret_ptr_int (void){
    return _error_0;            // E1
    return _ptr_void;           // E1
    return _ptr_ptr_void;       //* E1
    return _error_1;            // E1
    return _char;               //* E1
    return _ptr_char;           //* E1
    return _ptr_ptr_char;       //* E1
    return _arr_char_10;        //* E1
    return _ptr_arr_char_10;    //* E1
    return _int;                //* E1
    return _ptr_int;            // E1
    return _ptr_ptr_int;        //* E1
    return _arr_int_10;         // E1
    return _ptr_arr_int_10;     //* E1
    return _long;               //* E1
    return _ptr_long;           //* E1
    return _ptr_ptr_long;       //* E1
    return _arr_long_10;        //* E1
    return _ptr_arr_long_10;    //* E1
}
int **  _fexpect_ret_ptr_ptr_int (void){
    return _error_0;            // E1
    return _ptr_void;           // E1
    return _ptr_ptr_void;       //* E1
    return _error_1;            // E1
    return _char;               //* E1
    return _ptr_char;           //* E1
    return _ptr_ptr_char;       //* E1
    return _arr_char_10;        //* E1
    return _ptr_arr_char_10;    //* E1
    return _int;                //* E1
    return _ptr_int;            //* E1
    return _ptr_ptr_int;        // E1
    return _arr_int_10;         //* E1
    return _ptr_arr_int_10;     // E1
    return _long;               //* E1
    return _ptr_long;           //* E1
    return _ptr_ptr_long;       //* E1
    return _arr_long_10;        //* E1
    return _ptr_arr_long_10;    //* E1
}
long    _fexpect_ret_long(void){
    return _error_0;            // E1
    return _ptr_void;           //* E1
    return _ptr_ptr_void;       //* E1
    return _error_1;            // E1
    return _char;               // E1
    return _ptr_char;           //* E1
    return _ptr_ptr_char;       //* E1
    return _arr_char_10;        //* E1
    return _ptr_arr_char_10;    //* E1
    return _int;                // E1
    return _ptr_int;            //* E1
    return _ptr_ptr_int;        //* E1
    return _arr_int_10;         //* E1
    return _ptr_arr_int_10;     //* E1
    return _long;               // E1
    return _ptr_long;           //* E1
    return _ptr_ptr_long;       //* E1
    return _arr_long_10;        //* E1
    return _ptr_arr_long_10;    //* E1
}
long*   _fexpect_ret_ptr_long(void){
    return _error_0;            // E1
    return _ptr_void;           // E1
    return _ptr_ptr_void;       //* E1
    return _error_1;            // E1
    return _char;               //* E1
    return _ptr_char;           //* E1
    return _ptr_ptr_char;       //* E1
    return _arr_char_10;        //* E1
    return _ptr_arr_char_10;    //* E1
    return _int;                //* E1
    return _ptr_int;            //* E1
    return _ptr_ptr_int;        //* E1
    return _arr_int_10;         //* E1
    return _ptr_arr_int_10;     //* E1
    return _long;               //* E1
    return _ptr_long;           // E1
    return _ptr_ptr_long;       //* E1
    return _arr_long_10;        // E1
    return _ptr_arr_long_10;    //* E1
}
long**  _fexpect_ret_ptr_ptr_long(void){
    return _error_0;            // E1
    return _ptr_void;           // E1
    return _ptr_ptr_void;       //* E1
    return _error_1;            // E1
    return _char;               //* E1
    return _ptr_char;           //* E1
    return _ptr_ptr_char;       //* E1
    return _arr_char_10;        //* E1
    return _ptr_arr_char_10;    //* E1
    return _int;                //* E1
    return _ptr_int;            //* E1
    return _ptr_ptr_int;        //* E1
    return _arr_int_10;         //* E1
    return _ptr_arr_int_10;     //* E1
    return _long;               //* E1
    return _ptr_long;           //* E1
    return _ptr_ptr_long;       // E1
    return _arr_long_10;        //* E1
    return _ptr_arr_long_10;    // E1
}

int main(void) {
    // Testing
}