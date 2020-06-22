#include "String.h" // include definition of class String
#include <iostream>
string::string()
   : bx(),
     mySize( 0 ),
     myRes( 15 )
{
}

string::string( const char *const ptr, const size_type count )
   : bx(),
     mySize( 0 ),
     myRes( 15 )
{
    if (count > 15) // count > 15, 需定義新的空間, 原始Res為15, 所以不需刪除舊空間
    {
        size_type newMyRes = myRes * 3 / 2;
        if (newMyRes < (count / 16) * 16 + 15)
            newMyRes = (count / 16) * 16 + 15;
        bx.ptr = new value_type[newMyRes + 1]();
        myRes = newMyRes;
    }
    // count <= 15
    mySize = count;
    for (size_type i = 0; i < mySize; i++)
        myPtr()[i] = ptr[i];
    myPtr()[mySize] = '\0';
}

string::string( const size_type count, const char ch )
   : bx(),
     mySize( 0 ),
     myRes( 15 )
{
    if (count > 15) // count > 15, 需定義新的空間, 原始Res為15, 所以不需刪除舊空間
    {
        size_type newMyRes = myRes * 3 / 2;
        if (newMyRes < (count / 16) * 16 + 15)
            newMyRes = (count / 16) * 16 + 15;
        bx.ptr = new value_type[newMyRes + 1]();
        myRes = newMyRes;
    }
    // count <= 15
    mySize = count;
    for (size_type i = 0; i < mySize; i++)
        myPtr()[i] = ch;
    myPtr()[mySize] = '\0';
}

string::string( const string &right )
   : bx(),
     mySize( 0 ),
     myRes( 15 )
{
    if (right.mySize > 15) // right 的 size > 15, 需定義新的空間, 原始Res為15, 所以不需刪除舊空間
    {
        size_type newMyRes = myRes * 3 / 2;
        if (newMyRes < (right.mySize / 16) * 16 + 15)
            newMyRes = (right.mySize / 16) * 16 + 15;
        bx.ptr = new value_type[newMyRes + 1]();
        myRes = newMyRes;
    }
    // right 的 size <= 15 
    mySize = right.mySize;
    for (size_type i = 0; i < mySize; i++)
        myPtr()[i] = right.myPtr()[i];
    myPtr()[mySize] = '\0';
}

string::~string()
{
   if( myRes > 15 )
      delete[] bx.ptr;
}

string::value_type* string::myPtr()
{
   if( myRes < 16 )
      return bx.buf;
   else
      return bx.ptr;
}

const string::value_type* string::myPtr() const
{
   if( myRes < 16 )
      return bx.buf;
   else
      return bx.ptr;
}

string& string::assign( const string &right )
{
   if( this != &right )
   {
       if (right.mySize > myRes) // right 的 size > myRes, 需重新定義更大的空間
       {
           size_type newMyRes = myRes * 3 / 2;
           if (newMyRes < (right.mySize / 16) * 16 + 15)
               newMyRes = (right.mySize / 16) * 16 + 15;
           if (myRes > 15)
               delete[] bx.ptr;
           bx.ptr = new value_type[newMyRes + 1]();
           myRes = newMyRes;
       }
       // 空間足夠的情況
       mySize = right.mySize;
       for (size_type i = 0; i < mySize; i++)
           myPtr()[i] = right.myPtr()[i];
       myPtr()[mySize] = '\0';
   }
   return *this;
}

void string::clear()
{
   mySize = 0;
   myPtr()[ 0 ] = value_type();
}

string::iterator string::begin()
{
   return iterator( myPtr() );
}

string::const_iterator string::begin() const
{
   return const_iterator( myPtr() );
}

string::iterator string::end()
{
   return iterator( myPtr() + static_cast< difference_type >( mySize ) );
}

string::const_iterator string::end() const
{
   return const_iterator( myPtr() + static_cast< difference_type >( mySize ) );
}

string::reference string::element( const size_type off )
{
   return myPtr()[ off ];
}

string::const_reference string::element( const size_type off ) const
{
   return myPtr()[ off ];
}

void string::push_back( char ch )
{
   resize( mySize + 1 );
   myPtr()[ mySize - 1 ] = ch;
}

void string::pop_back()
{
   if( mySize > 0 )
      --mySize;
}

string::reference string::front()
{
   return myPtr()[ 0 ];
}

string::const_reference string::front() const
{
   return myPtr()[ 0 ];
}

string::reference string::back()
{
   return myPtr()[ mySize - 1 ];
}

string::const_reference string::back() const
{
   return myPtr()[ mySize - 1 ];
}

const char* string::c_str() const
{
   return myPtr();
}

string::size_type string::size() const
{
   return mySize;
}

void string::resize( const size_type newSize, const char ch ) // 將多餘的空間填入ch
{
    if (newSize > myRes) // newSize > myRes 需重新定義更大的空間
    {
        size_type newMyRes = myRes * 3 / 2;
        if (newMyRes < (newSize / 16) * 16 + 15)
            newMyRes = (newSize / 16) * 16 + 15;
        value_type* str = new value_type[newMyRes + 1]();
        for (size_type i = 0; i < mySize; i++)
            str[i] = myPtr()[i];
        if (myRes > 15)
            delete[] bx.ptr;
        bx.ptr = str;
        myRes = newMyRes;
    }
    // 空間足夠的情況
    for (size_type i = mySize; i < newSize; i++) // 將 mySize ~ newSize 填入 ch
        myPtr()[i] = ch;
    mySize = newSize;
    myPtr()[mySize] = '\0';
}

string::size_type string::capacity() const
{
   return myRes;
}

bool string::empty() const
{
   return mySize == 0;
}