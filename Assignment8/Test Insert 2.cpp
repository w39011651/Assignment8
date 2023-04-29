#include <iostream>
using std::cout;
using std::endl;

#include <deque>
#include "deque.h"

template< typename T >
size_t compDequeSize();

template< typename T >
void testInsert();

template< typename T >
void testInsert1();

template< typename T >
void testInsert2();

template< typename T >
void testInsert3();

template< typename T >
bool equal( std::deque< T > &data1, deque< T > &data2 );

int main()
{
/**/
   testInsert< char >();

   testInsert< short >();

   testInsert< long >();

   testInsert< long long >();
/**/
   system( "pause" );
}

template< typename T >
void testInsert()
{
   testInsert1< T >();

   testInsert2< T >();

   testInsert3< T >();
}

// return number of elements per block (a power of 2)
template< typename T >
size_t compDequeSize()
{
   return sizeof( T ) <= 1 ? 16 : sizeof( T ) <= 2 ? 8 :
          sizeof( T ) <= 4 ?  4 : sizeof( T ) <= 8 ? 2 : 1;
}

template< typename T >
void testInsert1()
{
   size_t dequeSize = compDequeSize< T >(); // elements per block (a power of 2)

   const size_t maxMapSize = ( sizeof( T ) <= 2 ) ? 8 : 4 * sizeof( T );
   size_t numErrors = 0;

   for( size_t mapSize = 8; mapSize <= maxMapSize; mapSize *= 2 )
   {
      for( size_t myOff = 0; myOff < dequeSize * mapSize; ++myOff )
      {
         for( size_t mySize = 1; mySize <= dequeSize * mapSize; ++mySize )
         {
            for( size_t position = 0; position <= mySize; ++position )
            {
               deque< T > deque1;
               T ***map1 = reinterpret_cast< T *** > ( &deque1 );
               size_t *mapSize1 = reinterpret_cast< size_t * >( &deque1 ) + 1;
               size_t *myOff1 = reinterpret_cast< size_t * >( &deque1 ) + 2;
               size_t *mySize1 = reinterpret_cast< size_t * >( &deque1 ) + 3;

               *mapSize1 = mapSize;
               *map1 = new T * [ mapSize ]();
               *myOff1 = myOff;
               *mySize1 = mySize;

               for( size_t block = myOff / dequeSize; block <= ( myOff + mySize - 1 ) / dequeSize; block++ )
                  ( *map1 )[ block % mapSize ] = new T[ dequeSize ];

               for( size_t i = myOff; i < myOff + mySize; i++ )
               {
                  size_t block = i / dequeSize % mapSize;
                  ( *map1 )[ block ][ i % dequeSize ] = static_cast< T >( i );
               }

               deque1.insert( deque1.begin() + position, static_cast< T >( myOff + mySize ) );

               T ***map2 = reinterpret_cast< T *** > ( &deque1 );
               size_t *mapSize2 = reinterpret_cast< size_t * >( &deque1 ) + 1;
               size_t *myOff2 = reinterpret_cast< size_t * >( &deque1 ) + 2;
               size_t *mySize2 = reinterpret_cast< size_t * >( &deque1 ) + 3;

               if( position <= mySize / 2 )
               {
                  if( ( *myOff2 + 1 ) % ( dequeSize * mapSize ) != myOff )
                     numErrors++;
               }
               else
                  if( *myOff2 != myOff )
                     numErrors++;

               if( *mySize2 != mySize + 1 )
                  numErrors++;

               if( *mapSize2 == mapSize )
                  if( *map2 != *map1 )
                     numErrors++;

               for( size_t block = myOff / dequeSize; block <= ( myOff + mySize - 1 ) / dequeSize; block++ )
                  if( ( *map2 )[ block % mapSize ] != ( *map1 )[ block % mapSize ] )
                     numErrors++;
            }
         }

         if( ( mapSize == 4 * sizeof( T ) && myOff % 16 == 15 ) ||
             ( mapSize == 8 * sizeof( T ) && myOff % 4 == 3 ) )
             cout << "There are " << numErrors << " errors\n";
      }
   }

   cout << endl;
}

template< typename T >
void testInsert2()
{
   size_t numErrors = 0;
   deque< T > deque1;
   T ***map1 = reinterpret_cast< T *** > ( &deque1 );
   size_t *mapSize1 = reinterpret_cast< size_t * >( &deque1 ) + 1;
   size_t *myOff1 = reinterpret_cast< size_t * >( &deque1 ) + 2;
   size_t *mySize1 = reinterpret_cast< size_t * >( &deque1 ) + 3;

   *mapSize1 = 0;
   *myOff1 = 0;
   *mySize1 = 0;

   T value = 1 + rand() % 99;
   deque1.insert( deque1.begin(), value );

   T ***map2 = reinterpret_cast< T *** > ( &deque1 );
   size_t *mapSize2 = reinterpret_cast< size_t * >( &deque1 ) + 1;
   size_t *myOff2 = reinterpret_cast< size_t * >( &deque1 ) + 2;
   size_t *mySize2 = reinterpret_cast< size_t * >( &deque1 ) + 3;

   if( *myOff2 != 8 * compDequeSize< T >() - 1 )
      numErrors++;

   if( *mySize2 != 1 )
      numErrors++;

   if( *mapSize2 == 8 )
      if( *map2 != *map1 )
         numErrors++;

   cout << "There are " << numErrors << " errors\n\n";
}

template< typename T >
void testInsert3()
{
   size_t numErrors = 0;
   const size_t maxMapSize = 256;

   for( size_t mapSize = 8; mapSize <= maxMapSize; mapSize *= 2 )
   {
      deque< T > deque1;
      T ***map1 = reinterpret_cast< T *** > ( &deque1 );
      size_t *mapSize1 = reinterpret_cast< size_t * >( &deque1 ) + 1;
      size_t *myOff1 = reinterpret_cast< size_t * >( &deque1 ) + 2;
      size_t *mySize1 = reinterpret_cast< size_t * >( &deque1 ) + 3;

      *mapSize1 = mapSize;
      *map1 = new T * [ mapSize ]();
      *myOff1 = 0;
      *mySize1 = 0;

      T value = 1 + rand() % 99;
      deque1.insert( deque1.begin(), value );

      T ***map2 = reinterpret_cast< T *** > ( &deque1 );
      size_t *mapSize2 = reinterpret_cast< size_t * >( &deque1 ) + 1;
      size_t *myOff2 = reinterpret_cast< size_t * >( &deque1 ) + 2;
      size_t *mySize2 = reinterpret_cast< size_t * >( &deque1 ) + 3;

      if( *myOff2 != mapSize * compDequeSize< T >() - 1 )
         numErrors++;

      if( *mySize2 != 1 )
         numErrors++;

      if( *mapSize2 == mapSize )
         if( *map2 != *map1 )
            numErrors++;
   }

   cout << "There are " << numErrors << " errors\n\n";
}

template< typename T >
bool equal( std::deque< T > &data1, deque< T > &data2 )
{
   T **map1 = *( reinterpret_cast< T *** > ( &data1 ) + 1 );
   size_t mapSize1 = *( reinterpret_cast< size_t * >( &data1 ) + 2 );
   size_t myOff1 = *( reinterpret_cast< size_t * >( &data1 ) + 3 );
   size_t mySize1 = *( reinterpret_cast< size_t * >( &data1 ) + 4 );

   T **map2 = *( reinterpret_cast< T *** > ( &data2 ) );
   size_t mapSize2 = *( reinterpret_cast< size_t * >( &data2 ) + 1 );
   size_t myOff2 = *( reinterpret_cast< size_t * >( &data2 ) + 2 );
   size_t mySize2 = *( reinterpret_cast< size_t * >( &data2 ) + 3 );
/*
   cout << "mapSize1  " << mapSize1 << endl;
   cout << "mapSize2  " << mapSize2 << endl;
   cout << "myOff1  " << myOff1 << endl;
   cout << "myOff2  " << myOff2 << endl;
   cout << "mySize1  " << mySize1 << endl;
   cout << "mySize2  " << mySize2 << endl << endl;
*/
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
   for( size_t i = myOff1; i < myOff1 + mySize1; ++i/*, ++it2*/ )
//   for( size_t i = 0; i < dequeSize * mapSize1; ++i/*, ++it2*/ )
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