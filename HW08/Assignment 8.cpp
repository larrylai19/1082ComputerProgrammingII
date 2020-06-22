#include <iostream>
using std::cout;
using std::endl;

#include <iomanip>
using std::setw;

#include <deque>
#include "Deque - 1083316 - hw8.h"

void testDeque1( unsigned int size );
void testDeque2( unsigned int size );
void testDeque3( unsigned int size );
void testDeque4( unsigned int size );
void testDeque5();
bool equal( std::deque< int > &data1, deque< int > &data2 );

int main()
{
    
   for( int i = 1; i <= 10; i++ )
   {
      testDeque1( 8 * i );
      testDeque2( 8 * i );
      testDeque3( 8 * i );
      testDeque4( 8 * i );
   }

   cout << endl;
   
   for( unsigned int seed = 1; seed <= 50; seed++ )
   {
      srand( seed );
      testDeque5();
   }

   system( "pause" );
}

void testDeque1( unsigned int size )
{
   unsigned int numErrors = 8;
   for( unsigned int k = 0; k < 4; k++ )
   {
      std::deque< int > data1;
      unsigned int i;
      for( i = 1; i <= 4 * ( size / 2 - 1 ) + k; i++ )
         data1.push_back( i );
      for( ; i <= 4 * ( size - 1 ) + k; i++ )
         data1.push_front( i );

      deque< int > data2;
      unsigned int j;
      for( j = 1; j <= 4 * ( size / 2 - 1 ) + k; j++ )
         data2.push_back( j );
      for( ; j <= 4 * ( size - 1 ) + k; j++ )
         data2.push_front( j );

      if( equal( data1, data2 ) )
         numErrors--;

      data1.push_front( i );
      data2.push_front( j );

      if( equal( data1, data2 ) )
         numErrors--;
   }
   cout << "There are " << numErrors << " errors.\n";
}

void testDeque2( unsigned int size )
{
   unsigned int numErrors = 8;
   for( unsigned int k = 0; k < 4; k++ )
   {
      std::deque< int > data1;
      unsigned int i;
      for( i = 1; i <= 4 * ( size / 2 - 1 ) + k; i++ )
         data1.push_back( i );
      for( ; i <= 4 * ( size - 1 ) + k; i++ )
         data1.push_front( i );

      deque< int > data2;
      unsigned int j;
      for( j = 1; j <= 4 * ( size / 2 - 1 ) + k; j++ )
         data2.push_back( j );
      for( ; j <= 4 * ( size - 1 ) + k; j++ )
         data2.push_front( j );

      if( equal( data1, data2 ) )
         numErrors--;

      data1.push_back( i );
      data2.push_back( j );

      if( equal( data1, data2 ) )
         numErrors--;
   }
   cout << "There are " << numErrors << " errors.\n";
}

void testDeque3( unsigned int size )
{
   unsigned int numErrors = 8;
   for( unsigned int k = 0; k < 4; k++ )
   {
      std::deque< int > data1;
      unsigned int i;
      for( i = 1; i <= 4 * ( size / 2 - 1 ) + k; i++ )
         data1.push_front( i );
      for( ; i <= 4 * ( size - 1 ) + k; i++ )
         data1.push_back( i );

      deque< int > data2;
      unsigned int j;
      for( j = 1; j <= 4 * ( size / 2 - 1 ) + k; j++ )
         data2.push_front( j );
      for( ; j <= 4 * ( size - 1 ) + k; j++ )
         data2.push_back( j );

      if( equal( data1, data2 ) )
         numErrors--;

      data1.push_back( i );
      data2.push_back( j );

      if( equal( data1, data2 ) )
         numErrors--;
   }
   cout << "There are " << numErrors << " errors.\n";
}

void testDeque4( unsigned int size )
{
   unsigned int numErrors = 8;
   for( unsigned int k = 0; k < 4; k++ )
   {
      std::deque< int > data1;
      unsigned int i;
      for( i = 1; i <= 4 * ( size / 2 - 1 ) + k; i++ )
         data1.push_front( i );
      for( ; i <= 4 * ( size - 1 ) + k; i++ )
         data1.push_back( i );

      deque< int > data2;
      unsigned int j;
      for( j = 1; j <= 4 * ( size / 2 - 1 ) + k; j++ )
         data2.push_front( j );
      for( ; j <= 4 * ( size - 1 ) + k; j++ )
         data2.push_back( j );

      if( equal( data1, data2 ) )
         numErrors--;

      data1.push_front( i );
      data2.push_front( j );

      if( equal( data1, data2 ) )
         numErrors--;
   }
   cout << "There are " << numErrors << " errors.\n";
}

void testDeque5()
{
   std::deque< int > data1;
   deque< int > data2;

   unsigned int numErrors = 1001;
   if( equal( data1, data2 ) )
      numErrors--;

   int value;
   for( unsigned int i = 0; i < 1000; i++ )
   {
      switch( rand() % 4 )
      {
      case 0:         
         value = 1 + rand() % 99;
         data1.push_front( value );
         data2.push_front( value );
         break;
      case 1:
         if( data1.size() > 0 )
         {
            data1.pop_front();
            data2.pop_front();
         }
         break;
      case 2:         
         value = 1 + rand() % 99;
         data1.push_back( value );
         data2.push_back( value );
         break;
      case 3:
         if( data1.size() > 0 )
         {
            data1.pop_back();
            data2.pop_back();
         }
         break;
      }

      if( equal( data1, data2 ) )
         numErrors--;
   }

   cout << "There are " << numErrors << " errors.\n";
}

bool equal( std::deque< int > &data1, deque< int > &data2 )
{
   int **map1 = *( reinterpret_cast< int *** > ( &data1 ) + 1 );
   unsigned int mapSize1 = *( reinterpret_cast< unsigned int * >( &data1 ) + 2 );
   unsigned int myOff1 = *( reinterpret_cast< unsigned int * >( &data1 ) + 3 );
   unsigned int mySize1 = *( reinterpret_cast< unsigned int * >( &data1 ) + 4 );

   unsigned int **map2 = *( reinterpret_cast< unsigned int *** > ( &data2 ) );
   unsigned int mapSize2 = *( reinterpret_cast< unsigned int * >( &data2 ) + 1 );
   unsigned int myOff2 = *( reinterpret_cast< unsigned int * >( &data2 ) + 2 );
   unsigned int mySize2 = *( reinterpret_cast< unsigned int * >( &data2 ) + 3 );

   if( mapSize1 != mapSize2 )
      return false;

   if( mapSize2 == 0 )
      if( mySize2 == 0 && myOff2 == 0 && map2 == nullptr )
         return true;
      else
         return false;

      if( myOff1 != myOff2 )
         return false;

   if( mySize1 != mySize2 )
      return false;

   deque< int >::iterator it2( data2.begin() );
   unsigned int row, col;
   for( unsigned int i = myOff1; i < myOff1 + mySize1; ++i, ++it2 )
   {
      row = ( i / 4 ) % mapSize1;
      if( map1[ row ] != nullptr && map2[ row ] == nullptr )
         return false;

      if( map1[ row ] == nullptr && map2[ row ] != nullptr )
         return false;

      if( map1[ row ] != nullptr && map2[ row ] != nullptr )
      {
         col = i % 4;
         if( map1[ row ][ col ] != map2[ row ][ col ] )
            return false;
         if( *it2 != map2[ row ][ col ] )
            return false;
      }
   }

   std::deque< int >::iterator it1( data1.begin() );
   deque< int > *myCont2;
   unsigned int offset1;
   unsigned int offset2;
   for( it2 = data2.begin(); it2 < data2.end(); ++it1, ++it2 )
   {
      myCont2 = *( reinterpret_cast< deque< int > ** >( &it2 ) );
      if( myCont2 != &data2 )
         return false;

      offset1 = *( reinterpret_cast< unsigned int * >( &it1 ) + 2 );
      offset2 = *( reinterpret_cast< unsigned int * >( &it2 ) + 1 );
      if( offset1 != offset2 )
         return false;
   }

   std::deque< int >::reverse_iterator rIt1( data1.rbegin() );
   deque< int >::reverse_iterator rIt2( data2.rbegin() );
   for( rIt2 = data2.rbegin(); rIt2 < data2.rend(); ++rIt1, ++rIt2 )
   {
      myCont2 = *( reinterpret_cast< deque< int > ** >( &rIt2 ) );
      if( myCont2 != &data2 )
         return false;

      offset1 = *( reinterpret_cast< unsigned int * >( &rIt1 ) + 2 );
      offset2 = *( reinterpret_cast< unsigned int * >( &rIt2 ) + 1 );
      if( offset1 != offset2 )
         return false;
   }

   return true;
}