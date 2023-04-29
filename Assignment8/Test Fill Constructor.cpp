#include <iostream>
using std::cout;
using std::endl;

#include <deque>
#include "deque.h"

template< typename T >
void testFillConstructor();

template< typename T >
size_t compDequeSize();

template< typename T >
bool equal( std::deque< T > &deque1, deque< T > &deque2 );

int main()
{
   testFillConstructor< char >();
   testFillConstructor< short >();
   testFillConstructor< long >();
   testFillConstructor< long long >();
   system( "pause" );
}

template< typename T >
void testFillConstructor()
{
   size_t numErrors = 0;

   T value = static_cast< T >( rand() );
   std::deque< T > deque1( 0, value );
   deque< T > deque2( 0, value );
   if( !equal( deque1, deque2 ) )
      numErrors++;

   for( int i = 0; i < 20; i++ )
   {
      size_t count = rand();
      T value = static_cast< T >( rand() );
      std::deque< T > deque1( count, value );
      deque< T > deque2( count, value );

      if( !equal( deque1, deque2 ) )
         numErrors++;
   }

   cout << "There are " << numErrors << " errors\n\n";
}

// return number of elements per block (a power of 2)
template< typename T >
size_t compDequeSize()
{
   return sizeof( T ) <= 1 ? 16 : sizeof( T ) <= 2 ? 8 :
          sizeof( T ) <= 4 ?  4 : sizeof( T ) <= 8 ? 2 : 1;
}

template< typename T >
bool equal( std::deque< T > &deque1, deque< T > &deque2 )
{
   T **map1 = *( reinterpret_cast< T *** > ( &deque1 ) + 1 );
   size_t mapSize1 = *( reinterpret_cast< size_t * >( &deque1 ) + 2 );
   size_t myOff1 = *( reinterpret_cast< size_t * >( &deque1 ) + 3 );
   size_t mySize1 = *( reinterpret_cast< size_t * >( &deque1 ) + 4 );

   T **map2 = *( reinterpret_cast< T *** > ( &deque2 ) );
   size_t mapSize2 = *( reinterpret_cast< size_t * >( &deque2 ) + 1 );
   size_t myOff2 = *( reinterpret_cast< size_t * >( &deque2 ) + 2 );
   size_t mySize2 = *( reinterpret_cast< size_t * >( &deque2 ) + 3 );

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

   size_t dequeSize = compDequeSize< T >(); // elements per block (a power of 2)

   size_t row, col;
//   for( size_t i = myOff1; i < myOff1 + mySize1; ++i )
   for( size_t i = 0; i < dequeSize * mapSize1; ++i )
   {
      row = ( i / dequeSize ) % mapSize1;
      if( map1[ row ] != nullptr && map2[ row ] == nullptr )
         return false;

      if( map1[ row ] == nullptr && map2[ row ] != nullptr )
         return false;

      if( map1[ row ] != nullptr && map2[ row ] != nullptr )
      {
         col = i % dequeSize;
         if( map1[ row ][ col ] != map2[ row ][ col ] )
            return false;
      }
   }

   return true;
}