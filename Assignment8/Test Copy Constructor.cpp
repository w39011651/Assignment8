#include <iostream>
using std::cout;
using std::endl;

#include <deque>
#include "Student ID - deque - copy constructor.h"

template< typename T >
size_t compDequeSize();

template< typename T >
void testCopyConstructor();

template< typename T >
void testCopyConstructor1();

template< typename T >
void testCopyConstructor2();

template< typename T >
void testCopyConstructor6();

template< typename T >
void testCopyConstructor7();

template< typename T >
void testCopyConstructor8();

template< typename T >
void testCopyConstructor9();

template< typename T >
void testCopyConstructor10();

template< typename T >
bool equal( std::deque< T > &deque1, deque< T > &deque2 );

int main()
{
   testCopyConstructor< char >();

   testCopyConstructor< short >();

   testCopyConstructor< long >();

   testCopyConstructor< long long >();

   system( "pause" );
}

template< typename T >
void testCopyConstructor()
{
/*
*/
   testCopyConstructor1< T >();
   testCopyConstructor2< T >();
   testCopyConstructor6< T >();
   testCopyConstructor7< T >();
   testCopyConstructor8< T >();
   testCopyConstructor9< T >();
   testCopyConstructor10< T >();
/*
*/
}

// return number of elements per block (a power of 2)
template< typename T >
size_t compDequeSize()
{
   return sizeof( T ) <= 1 ? 16 : sizeof( T ) <= 2 ? 8 :
          sizeof( T ) <= 4 ?  4 : sizeof( T ) <= 8 ? 2 : 1;
}

template< typename T >
void testCopyConstructor1()
{
   size_t dequeSize = compDequeSize< T >(); // elements per block (a power of 2)

   const size_t maxMapSize = 8 * sizeof( T );
   size_t numErrors = 0;

   for( size_t mapSize = 8; mapSize <= maxMapSize; mapSize *= 2 )
      for( size_t myOff = 0; myOff < dequeSize * ( mapSize + 1 ); ++myOff )
      {
         for( size_t mySize = 1; mySize <= dequeSize * mapSize; ++mySize )
         {
            std::deque< T > deque1;
            T ***map1 = reinterpret_cast< T *** > ( &deque1 ) + 1;
            size_t *mapSize1 = reinterpret_cast< size_t * >( &deque1 ) + 2;
            size_t *myOff1 = reinterpret_cast< size_t * >( &deque1 ) + 3;
            size_t *mySize1 = reinterpret_cast< size_t * >( &deque1 ) + 4;

            deque< T > deque2;
            T ***map2 = reinterpret_cast< T *** > ( &deque2 );
            size_t *mapSize2 = reinterpret_cast< size_t * >( &deque2 ) + 1;
            size_t *myOff2 = reinterpret_cast< size_t * >( &deque2 ) + 2;
            size_t *mySize2 = reinterpret_cast< size_t * >( &deque2 ) + 3;

            *mapSize1 = mapSize;
            *mapSize2 = mapSize;
            *map1 = new T*[ mapSize ]();
            *map2 = new T*[ mapSize ]();
            *myOff1 = myOff;
            *myOff2 = myOff;
            *mySize1 = mySize;
            *mySize2 = mySize;

            for( size_t block = myOff / dequeSize; block <= ( myOff + mySize - 1 ) / dequeSize; block++ )
            {
               ( *map1 )[ block % mapSize ] = new T[ dequeSize ];
               ( *map2 )[ block % mapSize ] = new T[ dequeSize ];
            }

            for( size_t i = myOff; i < myOff + mySize; i++ )
            {
               size_t block = i % ( dequeSize * mapSize ) / dequeSize;
               ( *map1 )[ block ][ i % dequeSize ] = static_cast< T >( i );
               ( *map2 )[ block ][ i % dequeSize ] = static_cast< T >( i );
            }

            std::deque< T > deque3( deque1 );
            deque< T > deque4( deque2 );

            if( !equal( deque3, deque4 ) )
               numErrors++;
         }

         if( ( mapSize == 4 * sizeof( T ) && myOff % 64 == 63 ) ||
             ( mapSize == 8 * sizeof( T ) && myOff % 32 == 31 ) )
             cout << "There are " << numErrors << " errors\n";
      }

   cout << endl;
}

template< typename T >
void testCopyConstructor2()
{
   size_t dequeSize = compDequeSize< T >(); // elements per block (a power of 2)

   const size_t maxMapSize = 32 * sizeof( T );
   size_t numErrors = 0;

   for( size_t mapSize = 8; mapSize <= maxMapSize; mapSize *= 2 )
   {
      for( size_t myOff = 0; myOff < dequeSize * ( mapSize + 1 ); ++myOff )
      {
         for( size_t mySize = 1; mySize <= 8; ++mySize )
         {
            std::deque< T > deque1;
            T ***map1 = reinterpret_cast< T *** > ( &deque1 ) + 1;
            size_t *mapSize1 = reinterpret_cast< size_t * >( &deque1 ) + 2;
            size_t *myOff1 = reinterpret_cast< size_t * >( &deque1 ) + 3;
            size_t *mySize1 = reinterpret_cast< size_t * >( &deque1 ) + 4;

            deque< T > deque2;
            T ***map2 = reinterpret_cast< T *** > ( &deque2 );
            size_t *mapSize2 = reinterpret_cast< size_t * >( &deque2 ) + 1;
            size_t *myOff2 = reinterpret_cast< size_t * >( &deque2 ) + 2;
            size_t *mySize2 = reinterpret_cast< size_t * >( &deque2 ) + 3;

            *mapSize1 = mapSize;
            *mapSize2 = mapSize;
            *map1 = new T*[ mapSize ]();
            *map2 = new T*[ mapSize ]();
            *myOff1 = myOff;
            *myOff2 = myOff;
            *mySize1 = mySize;
            *mySize2 = mySize;

            for( size_t block = myOff / dequeSize; block <= ( myOff + mySize - 1 ) / dequeSize; block++ )
            {
               ( *map1 )[ block % mapSize ] = new T[ dequeSize ];
               ( *map2 )[ block % mapSize ] = new T[ dequeSize ];
            }

            for( size_t i = myOff; i < myOff + mySize; i++ )
            {
               size_t block = i % ( dequeSize * mapSize ) / dequeSize;
               ( *map1 )[ block ][ i % dequeSize ] = static_cast< T >( i );
               ( *map2 )[ block ][ i % dequeSize ] = static_cast< T >( i );
            }

            std::deque< T > deque3( deque1 );
            deque< T > deque4( deque2 );

            if( !equal( deque3, deque4 ) )
               numErrors++;
         }
      }
   }

   cout << "There are " << numErrors << " errors\n";
}

template< typename T >
void testCopyConstructor6()
{
   size_t dequeSize = compDequeSize< T >(); // elements per block (a power of 2)

   const size_t maxMapSize = 256;

   size_t numErrors = 0;

   for( size_t mapSize = 8; mapSize <= maxMapSize; mapSize *= 2 )
   {
      for( size_t myOff = 0; myOff < 8; ++myOff )
      {
         for( size_t mySize = 1; mySize <= 8; ++mySize )
         {
            std::deque< T > deque1;
            T ***map1 = reinterpret_cast< T *** > ( &deque1 ) + 1;
            size_t *mapSize1 = reinterpret_cast< size_t * >( &deque1 ) + 2;
            size_t *myOff1 = reinterpret_cast< size_t * >( &deque1 ) + 3;
            size_t *mySize1 = reinterpret_cast< size_t * >( &deque1 ) + 4;

            deque< T > deque2;
            T ***map2 = reinterpret_cast< T *** > ( &deque2 );
            size_t *mapSize2 = reinterpret_cast< size_t * >( &deque2 ) + 1;
            size_t *myOff2 = reinterpret_cast< size_t * >( &deque2 ) + 2;
            size_t *mySize2 = reinterpret_cast< size_t * >( &deque2 ) + 3;

            *mapSize1 = mapSize;
            *mapSize2 = mapSize;
            *map1 = new T*[ mapSize ]();
            *map2 = new T*[ mapSize ]();
            *myOff1 = myOff;
            *myOff2 = myOff;
            *mySize1 = mySize;
            *mySize2 = mySize;

            for( size_t block = myOff / dequeSize; block <= ( myOff + mySize - 1 ) / dequeSize; block++ )
            {
               ( *map1 )[ block % mapSize ] = new T[ dequeSize ];
               ( *map2 )[ block % mapSize ] = new T[ dequeSize ];
            }

            for( size_t i = myOff; i < myOff + mySize; i++ )
            {
               size_t block = i % ( dequeSize * mapSize ) / dequeSize;
               ( *map1 )[ block ][ i % dequeSize ] = static_cast< T >( i );
               ( *map2 )[ block ][ i % dequeSize ] = static_cast< T >( i );
            }

            std::deque< T > deque3( deque1 );
            deque< T > deque4( deque2 );

            if( !equal( deque3, deque4 ) )
               numErrors++;
         }
      }
   }

   cout << "There are " << numErrors << " errors\n";
}

template< typename T >
void testCopyConstructor7()
{
   size_t dequeSize = compDequeSize< T >(); // elements per block (a power of 2)

   const size_t maxMapSize = 32 * sizeof( T );

   size_t numErrors = 0;

   for( size_t mapSize = 8; mapSize <= maxMapSize; mapSize *= 2 )
   {
      for( size_t myOff = 0; myOff < 8; ++myOff )
      {
         for( size_t mySize = dequeSize * ( mapSize - 2 ); mySize <= dequeSize * mapSize; ++mySize )
         {
            std::deque< T > deque1;
            T ***map1 = reinterpret_cast< T *** > ( &deque1 ) + 1;
            size_t *mapSize1 = reinterpret_cast< size_t * >( &deque1 ) + 2;
            size_t *myOff1 = reinterpret_cast< size_t * >( &deque1 ) + 3;
            size_t *mySize1 = reinterpret_cast< size_t * >( &deque1 ) + 4;

            deque< T > deque2;
            T ***map2 = reinterpret_cast< T *** > ( &deque2 );
            size_t *mapSize2 = reinterpret_cast< size_t * >( &deque2 ) + 1;
            size_t *myOff2 = reinterpret_cast< size_t * >( &deque2 ) + 2;
            size_t *mySize2 = reinterpret_cast< size_t * >( &deque2 ) + 3;

            *mapSize1 = mapSize;
            *mapSize2 = mapSize;
            *map1 = new T*[ mapSize ]();
            *map2 = new T*[ mapSize ]();
            *myOff1 = myOff;
            *myOff2 = myOff;
            *mySize1 = mySize;
            *mySize2 = mySize;

            for( size_t block = myOff / dequeSize; block <= ( myOff + mySize - 1 ) / dequeSize; block++ )
            {
               ( *map1 )[ block % mapSize ] = new T[ dequeSize ];
               ( *map2 )[ block % mapSize ] = new T[ dequeSize ];
            }

            for( size_t i = myOff; i < myOff + mySize; i++ )
            {
               size_t block = i % ( dequeSize * mapSize ) / dequeSize;
               ( *map1 )[ block ][ i % dequeSize ] = static_cast< T >( i );
               ( *map2 )[ block ][ i % dequeSize ] = static_cast< T >( i );
            }

            std::deque< T > deque3( deque1 );
            deque< T > deque4( deque2 );

            if( !equal( deque3, deque4 ) )
               numErrors++;
         }
      }
   }

   cout << "There are " << numErrors << " errors\n";
}

template< typename T >
void testCopyConstructor8()
{
   size_t dequeSize = compDequeSize< T >(); // elements per block (a power of 2)

   const size_t maxMapSize = 256;

   size_t numErrors = 0;

   for( size_t mapSize = 8; mapSize <= maxMapSize; mapSize *= 2 )
   {
      for( size_t myOff = dequeSize * ( mapSize - 2 ); myOff < dequeSize * ( mapSize + 1 ); ++myOff )
      {
         for( size_t mySize = 1; mySize <= 8; ++mySize )
         {
            std::deque< T > deque1;
            T ***map1 = reinterpret_cast< T *** > ( &deque1 ) + 1;
            size_t *mapSize1 = reinterpret_cast< size_t * >( &deque1 ) + 2;
            size_t *myOff1 = reinterpret_cast< size_t * >( &deque1 ) + 3;
            size_t *mySize1 = reinterpret_cast< size_t * >( &deque1 ) + 4;

            deque< T > deque2;
            T ***map2 = reinterpret_cast< T *** > ( &deque2 );
            size_t *mapSize2 = reinterpret_cast< size_t * >( &deque2 ) + 1;
            size_t *myOff2 = reinterpret_cast< size_t * >( &deque2 ) + 2;
            size_t *mySize2 = reinterpret_cast< size_t * >( &deque2 ) + 3;

            *mapSize1 = mapSize;
            *mapSize2 = mapSize;
            *map1 = new T*[ mapSize ]();
            *map2 = new T*[ mapSize ]();
            *myOff1 = myOff;
            *myOff2 = myOff;
            *mySize1 = mySize;
            *mySize2 = mySize;

            for( size_t block = myOff / dequeSize; block <= ( myOff + mySize - 1 ) / dequeSize; block++ )
            {
               ( *map1 )[ block % mapSize ] = new T[ dequeSize ];
               ( *map2 )[ block % mapSize ] = new T[ dequeSize ];
            }

            for( size_t i = myOff; i < myOff + mySize; i++ )
            {
               size_t block = i % ( dequeSize * mapSize ) / dequeSize;
               ( *map1 )[ block ][ i % dequeSize ] = static_cast< T >( i );
               ( *map2 )[ block ][ i % dequeSize ] = static_cast< T >( i );
            }

            std::deque< T > deque3( deque1 );
            deque< T > deque4( deque2 );

            if( !equal( deque3, deque4 ) )
               numErrors++;
         }
      }
   }

   cout << "There are " << numErrors << " errors\n";
}

template< typename T >
void testCopyConstructor9()
{
   size_t dequeSize = compDequeSize< T >(); // elements per block (a power of 2)

   const size_t maxMapSize = 16 * sizeof( T );

   size_t numErrors = 0;

   for( size_t mapSize = 8; mapSize <= maxMapSize; mapSize *= 2 )
   {
      for( size_t myOff = dequeSize * ( mapSize - 2 ); myOff < dequeSize * ( mapSize + 1 ); ++myOff )
      {
         for( size_t mySize = dequeSize * ( mapSize - 2 ); mySize <= dequeSize * mapSize; ++mySize )
         {
            std::deque< T > deque1;
            T ***map1 = reinterpret_cast< T *** > ( &deque1 ) + 1;
            size_t *mapSize1 = reinterpret_cast< size_t * >( &deque1 ) + 2;
            size_t *myOff1 = reinterpret_cast< size_t * >( &deque1 ) + 3;
            size_t *mySize1 = reinterpret_cast< size_t * >( &deque1 ) + 4;

            deque< T > deque2;
            T ***map2 = reinterpret_cast< T *** > ( &deque2 );
            size_t *mapSize2 = reinterpret_cast< size_t * >( &deque2 ) + 1;
            size_t *myOff2 = reinterpret_cast< size_t * >( &deque2 ) + 2;
            size_t *mySize2 = reinterpret_cast< size_t * >( &deque2 ) + 3;

            *mapSize1 = mapSize;
            *mapSize2 = mapSize;
            *map1 = new T*[ mapSize ]();
            *map2 = new T*[ mapSize ]();
            *myOff1 = myOff;
            *myOff2 = myOff;
            *mySize1 = mySize;
            *mySize2 = mySize;

            for( size_t block = myOff / dequeSize; block <= ( myOff + mySize - 1 ) / dequeSize; block++ )
            {
               ( *map1 )[ block % mapSize ] = new T[ dequeSize ];
               ( *map2 )[ block % mapSize ] = new T[ dequeSize ];
            }

            for( size_t i = myOff; i < myOff + mySize; i++ )
            {
               size_t block = i % ( dequeSize * mapSize ) / dequeSize;
               ( *map1 )[ block ][ i % dequeSize ] = static_cast< T >( i );
               ( *map2 )[ block ][ i % dequeSize ] = static_cast< T >( i );
            }

            std::deque< T > deque3( deque1 );
            deque< T > deque4( deque2 );

            if( !equal( deque3, deque4 ) )
               numErrors++;
         }
      }
   }

   cout << "There are " << numErrors << " errors\n";
}

template< typename T >
void testCopyConstructor10()
{
   size_t dequeSize = compDequeSize< T >(); // elements per block (a power of 2)

   const size_t maxMapSize = 256;
   size_t numErrors = 0;

   for( size_t mapSize = 8; mapSize <= maxMapSize; mapSize *= 2 )
   {
      std::deque< T > deque1;
      T ***map1 = reinterpret_cast< T *** > ( &deque1 ) + 1;
      size_t *mapSize1 = reinterpret_cast< size_t * >( &deque1 ) + 2;
      size_t *myOff1 = reinterpret_cast< size_t * >( &deque1 ) + 3;
      size_t *mySize1 = reinterpret_cast< size_t * >( &deque1 ) + 4;

      deque< T > deque2;
      T ***map2 = reinterpret_cast< T *** > ( &deque2 );
      size_t *mapSize2 = reinterpret_cast< size_t * >( &deque2 ) + 1;
      size_t *myOff2 = reinterpret_cast< size_t * >( &deque2 ) + 2;
      size_t *mySize2 = reinterpret_cast< size_t * >( &deque2 ) + 3;

      *mapSize1 = mapSize;
      *mapSize2 = mapSize;
      *map1 = new T*[ mapSize ]();
      *map2 = new T*[ mapSize ]();
      size_t myOff = 0;
      size_t mySize = 0;
      *myOff1 = myOff;
      *myOff2 = myOff;
      *mySize1 = mySize;
      *mySize2 = mySize;

      std::deque< T > deque3( deque1 );
      deque< T > deque4( deque2 );

      if( !equal( deque3, deque4 ) )
         numErrors++;
   }

   cout << "There are " << numErrors << " errors\n\n";
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
   for( size_t i = myOff1; i < myOff1 + mySize1; ++i )
//   for( size_t i = 0; i < dequeSize * mapSize1; ++i )
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