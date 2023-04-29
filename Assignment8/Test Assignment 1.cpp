#include <iostream>
using std::cout;
using std::endl;

#include <ctime>
using std::time;

#include <deque>
#include "deque.h"

template< typename T >
size_t compDequeSize();

template< typename T >
void testAssignment();

template< typename T >
void testAssignment1();

template< typename T >
void testAssignment2();

template< typename T >
void testAssignment4();


template< typename T >
void testAssignment11();

template< typename T >
void testAssignment13();

template< typename T >
void testAssignment15();

template< typename T >
void testAssignment16();

template< typename T >
void testAssignment17();

template< typename T >
void testAssignment18();


template< typename T >
void testAssignment21();

template< typename T >
void testAssignment23();

template< typename T >
void testAssignment25();

template< typename T >
void testAssignment26();

template< typename T >
void testAssignment27();

template< typename T >
void testAssignment28();

template< typename T >
bool equal( std::deque< T > &deque1, deque< T > &deque2 );

int main()
{
   time_t t = time( nullptr );

   testAssignment< char >();

   testAssignment< short >();

   testAssignment< long >();

   testAssignment< long long >();

   cout << time( nullptr ) - t << " seconds\n\n";

   system( "pause" );
}

template< typename T >
void testAssignment()
{
/*
*/   if( sizeof( T ) >= 4 )
      testAssignment1< T >(); // very long execution time

   testAssignment2< T >();
   testAssignment4< T >();

   testAssignment11< T >();
   testAssignment13< T >();
   testAssignment15< T >();
   testAssignment16< T >();
   testAssignment17< T >();
   testAssignment18< T >();

   testAssignment21< T >();
   testAssignment23< T >();
   testAssignment25< T >();
   testAssignment26< T >();
   testAssignment27< T >();

   testAssignment28< T >();
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
void testAssignment1()
{
   size_t dequeSize = compDequeSize< T >(); // elements per block (a power of 2)

   size_t numErrors = 0;
   size_t mapSizeA = 8;
   size_t mapSizeB = 8;
   for( size_t myOffA = 0; myOffA < dequeSize * mapSizeA; ++myOffA )
   {
      for( size_t mySizeA = 1; mySizeA <= dequeSize * mapSizeA - myOffA % dequeSize; ++mySizeA )
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

         *mapSize1 = mapSizeA;
         *mapSize2 = mapSizeA;
         *map1 = new T*[ mapSizeA ]();
         *map2 = new T*[ *mapSize2 ]();
         *myOff1 = myOffA;
         *myOff2 = myOffA;
         *mySize1 = mySizeA;
         *mySize2 = mySizeA;

         for( size_t block = myOffA / dequeSize; block <= ( myOffA + mySizeA - 1 ) / dequeSize; block++ )
         {
            ( *map1 )[ block % mapSizeA ] = new T[ dequeSize ];
            ( *map2 )[ block % mapSizeA ] = new T[ dequeSize ];
         }

         for( size_t i = myOffA; i < myOffA + mySizeA; i++ )
         {
            size_t block = i % ( dequeSize * mapSizeA ) / dequeSize;
            ( *map1 )[ block ][ i % dequeSize ] = static_cast< T >( i );
            ( *map2 )[ block ][ i % dequeSize ] = static_cast< T >( i );
         }

         for( size_t myOffB = 0; myOffB < dequeSize * mapSizeB; ++myOffB )
         {
            for( size_t mySizeB = 1; mySizeB <= dequeSize * mapSizeB - myOffB % dequeSize; ++mySizeB )
            {
               std::deque< T > deque3;
               T ***map3 = reinterpret_cast< T *** > ( &deque3 ) + 1;
               size_t *mapSize3 = reinterpret_cast< size_t * >( &deque3 ) + 2;
               size_t *myOff3 = reinterpret_cast< size_t * >( &deque3 ) + 3;
               size_t *mySize3 = reinterpret_cast< size_t * >( &deque3 ) + 4;

               deque< T > deque4;
               T ***map4 = reinterpret_cast< T *** > ( &deque4 );
               size_t *mapSize4 = reinterpret_cast< size_t * >( &deque4 ) + 1;
               size_t *myOff4 = reinterpret_cast< size_t * >( &deque4 ) + 2;
               size_t *mySize4 = reinterpret_cast< size_t * >( &deque4 ) + 3;

               *mapSize3 = mapSizeB;
               *mapSize4 = mapSizeB;
               *map3 = new T*[ mapSizeB ]();
               *map4 = new T*[ mapSizeB ]();
               *myOff3 = myOffB;
               *myOff4 = myOffB;
               *mySize3 = mySizeB;
               *mySize4 = mySizeB;

               for( size_t block = myOffB / dequeSize; block <= ( myOffB + mySizeB - 1 ) / dequeSize; block++ )
               {
                  ( *map3 )[ block % mapSizeB ] = new T[ dequeSize ];
                  ( *map4 )[ block % mapSizeB ] = new T[ dequeSize ];
               }

               for( size_t i = myOffB; i < myOffB + mySizeB; i++ )
               {
                  size_t block = i % ( dequeSize * mapSizeB ) / dequeSize;
                  ( *map3 )[ block ][ i % dequeSize ] = static_cast< T >( i );
                  ( *map4 )[ block ][ i % dequeSize ] = static_cast< T >( i );
               }

               deque3 = deque1;
               deque4 = deque2;

               if( !equal( deque3, deque4 ) )
                  numErrors++;
            }
         }
      }

      if( ( sizeof( T ) == 4 ) || ( sizeof( T ) == 8 && myOffA % 4 == 3 ) )
         cout << "There are " << numErrors << " errors\n";
   }

   cout << endl;
}

template< typename T >
void testAssignment2()
{
   size_t dequeSize = compDequeSize< T >(); // elements per block (a power of 2)

   const size_t maxMapSize = ( sizeof( T ) <= 2 ) ? 8 : 4 * sizeof( T );
   size_t numErrors = 0;

   for( size_t mapSizeA = 8; mapSizeA <= maxMapSize; mapSizeA *= 2 )
      for( size_t myOffA = 0; myOffA < dequeSize * mapSizeA; ++myOffA )
      {
         for( size_t mySizeA = 1; mySizeA <= dequeSize * mapSizeA - myOffA % dequeSize; ++mySizeA )
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

            *mapSize1 = mapSizeA;
            *mapSize2 = mapSizeA;
            *map1 = new T*[ mapSizeA ]();
            *map2 = new T*[ *mapSize2 ]();
            *myOff1 = myOffA;
            *myOff2 = myOffA;
            *mySize1 = mySizeA;
            *mySize2 = mySizeA;

            for( size_t block = myOffA / dequeSize; block <= ( myOffA + mySizeA - 1 ) / dequeSize; block++ )
            {
               ( *map1 )[ block % mapSizeA ] = new T[ dequeSize ];
               ( *map2 )[ block % mapSizeA ] = new T[ dequeSize ];
            }

            for( size_t i = myOffA; i < myOffA + mySizeA; i++ )
            {
               size_t block = i % ( dequeSize * mapSizeA ) / dequeSize;
               ( *map1 )[ block ][ i % dequeSize ] = static_cast< T >( i );
               ( *map2 )[ block ][ i % dequeSize ] = static_cast< T >( i );
            }

            for( size_t mapSizeB = 8; mapSizeB <= maxMapSize; mapSizeB *= 2 )
            {
               std::deque< T > deque3;
               T ***map3 = reinterpret_cast< T *** > ( &deque3 ) + 1;
               size_t *mapSize3 = reinterpret_cast< size_t * >( &deque3 ) + 2;
               size_t *myOff3 = reinterpret_cast< size_t * >( &deque3 ) + 3;
               size_t *mySize3 = reinterpret_cast< size_t * >( &deque3 ) + 4;

               deque< T > deque4;
               T ***map4 = reinterpret_cast< T *** > ( &deque4 );
               size_t *mapSize4 = reinterpret_cast< size_t * >( &deque4 ) + 1;
               size_t *myOff4 = reinterpret_cast< size_t * >( &deque4 ) + 2;
               size_t *mySize4 = reinterpret_cast< size_t * >( &deque4 ) + 3;

               *mapSize3 = mapSizeB;
               *mapSize4 = mapSizeB;
               *map3 = new T*[ mapSizeB ]();
               *map4 = new T*[ mapSizeB ]();
               *myOff3 = 0;
               *myOff4 = 0;
               *mySize3 = 0;
               *mySize4 = 0;

               deque3 = deque1;
               deque4 = deque2;

               if( !equal( deque3, deque4 ) )
                  numErrors++;
            }
         }

         if( myOffA % 32 == 31 )
            cout << "There are " << numErrors << " errors\n";
      }

   cout << endl;
}

template< typename T >
void testAssignment4()
{
   size_t dequeSize = compDequeSize< T >(); // elements per block (a power of 2)

   const size_t maxMapSize = 256;
   size_t numErrors = 0;

   for( size_t mapSizeA = 8; mapSizeA <= maxMapSize; mapSizeA *= 2 )
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

      *mapSize1 = mapSizeA;
      *mapSize2 = mapSizeA;
      *map1 = new T*[ mapSizeA ]();
      *map2 = new T*[ *mapSize2 ]();
      *myOff1 = 0;
      *myOff2 = 0;
      *mySize1 = 0;
      *mySize2 = 0;

      for( size_t mapSizeB = 8; mapSizeB <= maxMapSize; mapSizeB *= 2 )
      {
         std::deque< T > deque3;
         T ***map3 = reinterpret_cast< T *** > ( &deque3 ) + 1;
         size_t *mapSize3 = reinterpret_cast< size_t * >( &deque3 ) + 2;
         size_t *myOff3 = reinterpret_cast< size_t * >( &deque3 ) + 3;
         size_t *mySize3 = reinterpret_cast< size_t * >( &deque3 ) + 4;

         deque< T > deque4;
         T ***map4 = reinterpret_cast< T *** > ( &deque4 );
         size_t *mapSize4 = reinterpret_cast< size_t * >( &deque4 ) + 1;
         size_t *myOff4 = reinterpret_cast< size_t * >( &deque4 ) + 2;
         size_t *mySize4 = reinterpret_cast< size_t * >( &deque4 ) + 3;

         *mapSize3 = mapSizeB;
         *mapSize4 = mapSizeB;
         *map3 = new T*[ mapSizeB ]();
         *map4 = new T*[ mapSizeB ]();
         *myOff3 = 0;
         *myOff4 = 0;
         *mySize3 = 0;
         *mySize4 = 0;

         deque3 = deque1;
         deque4 = deque2;

         if( !equal( deque3, deque4 ) )
            numErrors++;
      }
   }

   cout << "There are " << numErrors << " errors\n\n";
}

template< typename T >
void testAssignment11()
{
   size_t dequeSize = compDequeSize< T >(); // elements per block (a power of 2)

   const size_t maxMapSize = 128;
   size_t numErrors = 0;

   for( size_t mapSizeA = 8; mapSizeA <= maxMapSize; mapSizeA *= 2 )
   {
      for( size_t myOffA = 0; myOffA < 8; ++myOffA )
      {
         for( size_t mySizeA = 1; mySizeA <= 8; ++mySizeA )
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

            *mapSize1 = mapSizeA;
            *mapSize2 = mapSizeA;
            *map1 = new T*[ mapSizeA ]();
            *map2 = new T*[ *mapSize2 ]();
            *myOff1 = myOffA;
            *myOff2 = myOffA;
            *mySize1 = mySizeA;
            *mySize2 = mySizeA;

            for( size_t block = myOffA / dequeSize; block <= ( myOffA + mySizeA - 1 ) / dequeSize; block++ )
            {
               ( *map1 )[ block % mapSizeA ] = new T[ dequeSize ];
               ( *map2 )[ block % mapSizeA ] = new T[ dequeSize ];
            }

            for( size_t i = myOffA; i < myOffA + mySizeA; i++ )
            {
               size_t block = i % ( dequeSize * mapSizeA ) / dequeSize;
               ( *map1 )[ block ][ i % dequeSize ] = static_cast< T >( i );
               ( *map2 )[ block ][ i % dequeSize ] = static_cast< T >( i );
            }

            for( size_t mapSizeB = 8; mapSizeB <= maxMapSize; mapSizeB *= 2 )
               for( size_t myOffB = 0; myOffB < 8; ++myOffB )
               {
                  for( size_t mySizeB = 1; mySizeB <= 8; ++mySizeB )
                  {
                     std::deque< T > deque3;
                     T ***map3 = reinterpret_cast< T *** > ( &deque3 ) + 1;
                     size_t *mapSize3 = reinterpret_cast< size_t * >( &deque3 ) + 2;
                     size_t *myOff3 = reinterpret_cast< size_t * >( &deque3 ) + 3;
                     size_t *mySize3 = reinterpret_cast< size_t * >( &deque3 ) + 4;

                     deque< T > deque4;
                     T ***map4 = reinterpret_cast< T *** > ( &deque4 );
                     size_t *mapSize4 = reinterpret_cast< size_t * >( &deque4 ) + 1;
                     size_t *myOff4 = reinterpret_cast< size_t * >( &deque4 ) + 2;
                     size_t *mySize4 = reinterpret_cast< size_t * >( &deque4 ) + 3;

                     *mapSize3 = mapSizeB;
                     *mapSize4 = mapSizeB;
                     *map3 = new T*[ mapSizeB ]();
                     *map4 = new T*[ mapSizeB ]();
                     *myOff3 = myOffB;
                     *myOff4 = myOffB;
                     *mySize3 = mySizeB;
                     *mySize4 = mySizeB;

                     for( size_t block = myOffB / dequeSize; block <= ( myOffB + mySizeB - 1 ) / dequeSize; block++ )
                     {
                        ( *map3 )[ block % mapSizeB ] = new T[ dequeSize ];
                        ( *map4 )[ block % mapSizeB ] = new T[ dequeSize ];
                     }

                     for( size_t i = myOffB; i < myOffB + mySizeB; i++ )
                     {
                        size_t block = i % ( dequeSize * mapSizeB ) / dequeSize;
                        ( *map3 )[ block ][ i % dequeSize ] = static_cast< T >( i );
                        ( *map4 )[ block ][ i % dequeSize ] = static_cast< T >( i );
                     }

                     deque3 = deque1;
                     deque4 = deque2;

                     if( !equal( deque3, deque4 ) )
                        numErrors++;
                  }
               }
         }

         if( ( sizeof( T ) == 1 || mapSizeA >= maxMapSize / 4 ) && myOffA % 8 == 7 )
            cout << "There are " << numErrors << " errors\n";
      }
   }

   cout << endl;
}

template< typename T >
void testAssignment13()
{
   size_t dequeSize = compDequeSize< T >(); // elements per block (a power of 2)

   const size_t maxMapSize = 32 * sizeof( T );
   size_t numErrors = 0;

   for( size_t mapSizeA = 8; mapSizeA <= maxMapSize; mapSizeA *= 2 )
   {
      for( size_t myOffA = 0; myOffA < 8; ++myOffA )
      {
         for( size_t mySizeA = 1; mySizeA <= 8; ++mySizeA )
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

            *mapSize1 = mapSizeA;
            *mapSize2 = mapSizeA;
            *map1 = new T*[ mapSizeA ]();
            *map2 = new T*[ *mapSize2 ]();
            *myOff1 = myOffA;
            *myOff2 = myOffA;
            *mySize1 = mySizeA;
            *mySize2 = mySizeA;

            for( size_t block = myOffA / dequeSize; block <= ( myOffA + mySizeA - 1 ) / dequeSize; block++ )
            {
               ( *map1 )[ block % mapSizeA ] = new T[ dequeSize ];
               ( *map2 )[ block % mapSizeA ] = new T[ dequeSize ];
            }

            for( size_t i = myOffA; i < myOffA + mySizeA; i++ )
            {
               size_t block = i % ( dequeSize * mapSizeA ) / dequeSize;
               ( *map1 )[ block ][ i % dequeSize ] = static_cast< T >( i );
               ( *map2 )[ block ][ i % dequeSize ] = static_cast< T >( i );
            }

            for( size_t mapSizeB = 8; mapSizeB <= maxMapSize; mapSizeB *= 2 )
               for( size_t myOffB = dequeSize * ( mapSizeB - 2 ); myOffB < dequeSize * mapSizeB; ++myOffB )
               {
                  for( size_t mySizeB = 1; mySizeB <= 8; ++mySizeB )
                  {
                     std::deque< T > deque3;
                     T ***map3 = reinterpret_cast< T *** > ( &deque3 ) + 1;
                     size_t *mapSize3 = reinterpret_cast< size_t * >( &deque3 ) + 2;
                     size_t *myOff3 = reinterpret_cast< size_t * >( &deque3 ) + 3;
                     size_t *mySize3 = reinterpret_cast< size_t * >( &deque3 ) + 4;

                     deque< T > deque4;
                     T ***map4 = reinterpret_cast< T *** > ( &deque4 );
                     size_t *mapSize4 = reinterpret_cast< size_t * >( &deque4 ) + 1;
                     size_t *myOff4 = reinterpret_cast< size_t * >( &deque4 ) + 2;
                     size_t *mySize4 = reinterpret_cast< size_t * >( &deque4 ) + 3;

                     *mapSize3 = mapSizeB;
                     *mapSize4 = mapSizeB;
                     *map3 = new T*[ mapSizeB ]();
                     *map4 = new T*[ mapSizeB ]();
                     *myOff3 = myOffB;
                     *myOff4 = myOffB;
                     *mySize3 = mySizeB;
                     *mySize4 = mySizeB;

                     for( size_t block = myOffB / dequeSize; block <= ( myOffB + mySizeB - 1 ) / dequeSize; block++ )
                     {
                        ( *map3 )[ block % mapSizeB ] = new T[ dequeSize ];
                        ( *map4 )[ block % mapSizeB ] = new T[ dequeSize ];
                     }

                     for( size_t i = myOffB; i < myOffB + mySizeB; i++ )
                     {
                        size_t block = i % ( dequeSize * mapSizeB ) / dequeSize;
                        ( *map3 )[ block ][ i % dequeSize ] = static_cast< T >( i );
                        ( *map4 )[ block ][ i % dequeSize ] = static_cast< T >( i );
                     }

                     deque3 = deque1;
                     deque4 = deque2;

                     if( !equal( deque3, deque4 ) )
                        numErrors++;
                  }
               }
         }

         if( ( sizeof( T ) == 1 || mapSizeA >= maxMapSize / 4 ) && myOffA % 8 == 7 )
            cout << "There are " << numErrors << " errors\n";
      }
   }

   cout << endl;
}

template< typename T >
void testAssignment15()
{
   size_t dequeSize = compDequeSize< T >(); // elements per block (a power of 2)

   const size_t maxMapSize = 8 * sizeof( T );
   size_t numErrors = 0;

   for( size_t mapSizeA = 8; mapSizeA <= maxMapSize; mapSizeA *= 2 )
      for( size_t myOffA = 0; myOffA < 8; ++myOffA )
      {
         for( size_t mySizeA = dequeSize * ( mapSizeA - 1 ); mySizeA <= dequeSize * mapSizeA - myOffA % dequeSize; ++mySizeA )
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

            *mapSize1 = mapSizeA;
            *mapSize2 = mapSizeA;
            *map1 = new T*[ mapSizeA ]();
            *map2 = new T*[ *mapSize2 ]();
            *myOff1 = myOffA;
            *myOff2 = myOffA;
            *mySize1 = mySizeA;
            *mySize2 = mySizeA;

            for( size_t block = myOffA / dequeSize; block <= ( myOffA + mySizeA - 1 ) / dequeSize; block++ )
            {
               ( *map1 )[ block % mapSizeA ] = new T[ dequeSize ];
               ( *map2 )[ block % mapSizeA ] = new T[ dequeSize ];
            }

            for( size_t i = myOffA; i < myOffA + mySizeA; i++ )
            {
               size_t block = i % ( dequeSize * mapSizeA ) / dequeSize;
               ( *map1 )[ block ][ i % dequeSize ] = static_cast< T >( i );
               ( *map2 )[ block ][ i % dequeSize ] = static_cast< T >( i );
            }

            for( size_t mapSizeB = 8; mapSizeB <= maxMapSize; mapSizeB *= 2 )
               for( size_t myOffB = 0; myOffB < 8; ++myOffB )
               {
                 for( size_t mySizeB = 1; mySizeB <= 8; ++mySizeB )
                  {
                     std::deque< T > deque3;
                     T ***map3 = reinterpret_cast< T *** > ( &deque3 ) + 1;
                     size_t *mapSize3 = reinterpret_cast< size_t * >( &deque3 ) + 2;
                     size_t *myOff3 = reinterpret_cast< size_t * >( &deque3 ) + 3;
                     size_t *mySize3 = reinterpret_cast< size_t * >( &deque3 ) + 4;

                     deque< T > deque4;
                     T ***map4 = reinterpret_cast< T *** > ( &deque4 );
                     size_t *mapSize4 = reinterpret_cast< size_t * >( &deque4 ) + 1;
                     size_t *myOff4 = reinterpret_cast< size_t * >( &deque4 ) + 2;
                     size_t *mySize4 = reinterpret_cast< size_t * >( &deque4 ) + 3;

                     *mapSize3 = mapSizeB;
                     *mapSize4 = mapSizeB;
                     *map3 = new T*[ mapSizeB ]();
                     *map4 = new T*[ mapSizeB ]();
                     *myOff3 = myOffB;
                     *myOff4 = myOffB;
                     *mySize3 = mySizeB;
                     *mySize4 = mySizeB;

                     for( size_t block = myOffB / dequeSize; block <= ( myOffB + mySizeB - 1 ) / dequeSize; block++ )
                     {
                        ( *map3 )[ block % mapSizeB ] = new T[ dequeSize ];
                        ( *map4 )[ block % mapSizeB ] = new T[ dequeSize ];
                     }

                     for( size_t i = myOffB; i < myOffB + mySizeB; i++ )
                     {
                        size_t block = i % ( dequeSize * mapSizeB ) / dequeSize;
                        ( *map3 )[ block ][ i % dequeSize ] = static_cast< T >( i );
                        ( *map4 )[ block ][ i % dequeSize ] = static_cast< T >( i );
                     }

                     deque3 = deque1;
                     deque4 = deque2;

                     if( !equal( deque3, deque4 ) )
                        numErrors++;
                  }
               }
         }

         if( ( sizeof( T ) == 1 && myOffA % 2 == 1 ) ||
             ( mapSizeA >= maxMapSize / 2 && myOffA % 4 == 3 ) )
             cout << "There are " << numErrors << " errors\n";
      }

   cout << endl;
}

template< typename T >
void testAssignment16()
{
   size_t dequeSize = compDequeSize< T >(); // elements per block (a power of 2)

   const size_t maxMapSize = 8 * sizeof( T );
   size_t numErrors = 0;

   for( size_t mapSizeA = 8; mapSizeA <= maxMapSize; mapSizeA *= 2 )
      for( size_t myOffA = 0; myOffA < 8; ++myOffA )
      {
         for( size_t mySizeA = dequeSize * ( mapSizeA - 1 ); mySizeA <= dequeSize * mapSizeA - myOffA % dequeSize; ++mySizeA )
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

            *mapSize1 = mapSizeA;
            *mapSize2 = mapSizeA;
            *map1 = new T*[ mapSizeA ]();
            *map2 = new T*[ *mapSize2 ]();
            *myOff1 = myOffA;
            *myOff2 = myOffA;
            *mySize1 = mySizeA;
            *mySize2 = mySizeA;

            for( size_t block = myOffA / dequeSize; block <= ( myOffA + mySizeA - 1 ) / dequeSize; block++ )
            {
               ( *map1 )[ block % mapSizeA ] = new T[ dequeSize ];
               ( *map2 )[ block % mapSizeA ] = new T[ dequeSize ];
            }

            for( size_t i = myOffA; i < myOffA + mySizeA; i++ )
            {
               size_t block = i % ( dequeSize * mapSizeA ) / dequeSize;
               ( *map1 )[ block ][ i % dequeSize ] = static_cast< T >( i );
               ( *map2 )[ block ][ i % dequeSize ] = static_cast< T >( i );
            }

            for( size_t mapSizeB = 8; mapSizeB <= maxMapSize; mapSizeB *= 2 )
               for( size_t myOffB = 0; myOffB < 8; ++myOffB )
               {
                  for( size_t mySizeB = dequeSize * ( mapSizeB - 1 ); mySizeB <= dequeSize * mapSizeB - myOffB % dequeSize; ++mySizeB )
                  {
                     std::deque< T > deque3;
                     T ***map3 = reinterpret_cast< T *** > ( &deque3 ) + 1;
                     size_t *mapSize3 = reinterpret_cast< size_t * >( &deque3 ) + 2;
                     size_t *myOff3 = reinterpret_cast< size_t * >( &deque3 ) + 3;
                     size_t *mySize3 = reinterpret_cast< size_t * >( &deque3 ) + 4;

                     deque< T > deque4;
                     T ***map4 = reinterpret_cast< T *** > ( &deque4 );
                     size_t *mapSize4 = reinterpret_cast< size_t * >( &deque4 ) + 1;
                     size_t *myOff4 = reinterpret_cast< size_t * >( &deque4 ) + 2;
                     size_t *mySize4 = reinterpret_cast< size_t * >( &deque4 ) + 3;

                     *mapSize3 = mapSizeB;
                     *mapSize4 = mapSizeB;
                     *map3 = new T*[ mapSizeB ]();
                     *map4 = new T*[ mapSizeB ]();
                     *myOff3 = myOffB;
                     *myOff4 = myOffB;
                     *mySize3 = mySizeB;
                     *mySize4 = mySizeB;

                     for( size_t block = myOffB / dequeSize; block <= ( myOffB + mySizeB - 1 ) / dequeSize; block++ )
                     {
                        ( *map3 )[ block % mapSizeB ] = new T[ dequeSize ];
                        ( *map4 )[ block % mapSizeB ] = new T[ dequeSize ];
                     }

                     for( size_t i = myOffB; i < myOffB + mySizeB; i++ )
                     {
                        size_t block = i % ( dequeSize * mapSizeB ) / dequeSize;
                        ( *map3 )[ block ][ i % dequeSize ] = static_cast< T >( i );
                        ( *map4 )[ block ][ i % dequeSize ] = static_cast< T >( i );
                     }

                     deque3 = deque1;
                     deque4 = deque2;

                     if( !equal( deque3, deque4 ) )
                        numErrors++;
                  }
               }
         }

         if( ( sizeof( T ) == 1 && myOffA % 2 == 1 ) ||
             ( mapSizeA >= maxMapSize / 2 && myOffA % 8 == 7 ) )
             cout << "There are " << numErrors << " errors\n";
      }

   cout << endl;
}

template< typename T >
void testAssignment17()
{
   size_t dequeSize = compDequeSize< T >(); // elements per block (a power of 2)

   const size_t maxMapSize = 8 * sizeof( T );
   size_t numErrors = 0;

   for( size_t mapSizeA = 8; mapSizeA <= maxMapSize; mapSizeA *= 2 )
      for( size_t myOffA = 0; myOffA < 8; ++myOffA )
      {
         for( size_t mySizeA = dequeSize * ( mapSizeA - 1 ); mySizeA <= dequeSize * mapSizeA - myOffA % dequeSize; ++mySizeA )
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

            *mapSize1 = mapSizeA;
            *mapSize2 = mapSizeA;
            *map1 = new T*[ mapSizeA ]();
            *map2 = new T*[ *mapSize2 ]();
            *myOff1 = myOffA;
            *myOff2 = myOffA;
            *mySize1 = mySizeA;
            *mySize2 = mySizeA;

            for( size_t block = myOffA / dequeSize; block <= ( myOffA + mySizeA - 1 ) / dequeSize; block++ )
            {
               ( *map1 )[ block % mapSizeA ] = new T[ dequeSize ];
               ( *map2 )[ block % mapSizeA ] = new T[ dequeSize ];
            }

            for( size_t i = myOffA; i < myOffA + mySizeA; i++ )
            {
               size_t block = i % ( dequeSize * mapSizeA ) / dequeSize;
               ( *map1 )[ block ][ i % dequeSize ] = static_cast< T >( i );
               ( *map2 )[ block ][ i % dequeSize ] = static_cast< T >( i );
            }

            for( size_t mapSizeB = 8; mapSizeB <= maxMapSize; mapSizeB *= 2 )
               for( size_t myOffB = dequeSize * ( mapSizeB - 1 ); myOffB < dequeSize * mapSizeB; ++myOffB )
               {
                  for( size_t mySizeB = 1; mySizeB <= 8; ++mySizeB )
                  {
                     std::deque< T > deque3;
                     T ***map3 = reinterpret_cast< T *** > ( &deque3 ) + 1;
                     size_t *mapSize3 = reinterpret_cast< size_t * >( &deque3 ) + 2;
                     size_t *myOff3 = reinterpret_cast< size_t * >( &deque3 ) + 3;
                     size_t *mySize3 = reinterpret_cast< size_t * >( &deque3 ) + 4;

                     deque< T > deque4;
                     T ***map4 = reinterpret_cast< T *** > ( &deque4 );
                     size_t *mapSize4 = reinterpret_cast< size_t * >( &deque4 ) + 1;
                     size_t *myOff4 = reinterpret_cast< size_t * >( &deque4 ) + 2;
                     size_t *mySize4 = reinterpret_cast< size_t * >( &deque4 ) + 3;

                     *mapSize3 = mapSizeB;
                     *mapSize4 = mapSizeB;
                     *map3 = new T*[ mapSizeB ]();
                     *map4 = new T*[ mapSizeB ]();
                     *myOff3 = myOffB;
                     *myOff4 = myOffB;
                     *mySize3 = mySizeB;
                     *mySize4 = mySizeB;

                     for( size_t block = myOffB / dequeSize; block <= ( myOffB + mySizeB - 1 ) / dequeSize; block++ )
                     {
                        ( *map3 )[ block % mapSizeB ] = new T[ dequeSize ];
                        ( *map4 )[ block % mapSizeB ] = new T[ dequeSize ];
                     }

                     for( size_t i = myOffB; i < myOffB + mySizeB; i++ )
                     {
                        size_t block = i % ( dequeSize * mapSizeB ) / dequeSize;
                        ( *map3 )[ block ][ i % dequeSize ] = static_cast< T >( i );
                        ( *map4 )[ block ][ i % dequeSize ] = static_cast< T >( i );
                     }

                     deque3 = deque1;
                     deque4 = deque2;

                     if( !equal( deque3, deque4 ) )
                        numErrors++;
                  }
               }
         }

         if( sizeof( T ) == 1 )
         {
            if( myOffA % 2 == 1 )
               cout << "There are " << numErrors << " errors\n";
         }
         else if( sizeof( T ) == 2 )
         {
            if( myOffA == 7 )
               cout << "There are " << numErrors << " errors\n";
         }
         else
            if( mapSizeA == maxMapSize && myOffA == 7 )
               cout << "There are " << numErrors << " errors\n";
      }

   cout << endl;
}

template< typename T >
void testAssignment18()
{
   size_t dequeSize = compDequeSize< T >(); // elements per block (a power of 2)

   const size_t maxMapSize = 8 * sizeof( T );
   size_t numErrors = 0;

   for( size_t mapSizeA = 8; mapSizeA <= maxMapSize; mapSizeA *= 2 )
      for( size_t myOffA = 0; myOffA < 8; ++myOffA )
      {
         for( size_t mySizeA = dequeSize * ( mapSizeA - 1 ); mySizeA <= dequeSize * mapSizeA - myOffA % dequeSize; ++mySizeA )
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

            *mapSize1 = mapSizeA;
            *mapSize2 = mapSizeA;
            *map1 = new T*[ mapSizeA ]();
            *map2 = new T*[ *mapSize2 ]();
            *myOff1 = myOffA;
            *myOff2 = myOffA;
            *mySize1 = mySizeA;
            *mySize2 = mySizeA;

            for( size_t block = myOffA / dequeSize; block <= ( myOffA + mySizeA - 1 ) / dequeSize; block++ )
            {
               ( *map1 )[ block % mapSizeA ] = new T[ dequeSize ];
               ( *map2 )[ block % mapSizeA ] = new T[ dequeSize ];
            }

            for( size_t i = myOffA; i < myOffA + mySizeA; i++ )
            {
               size_t block = i % ( dequeSize * mapSizeA ) / dequeSize;
               ( *map1 )[ block ][ i % dequeSize ] = static_cast< T >( i );
               ( *map2 )[ block ][ i % dequeSize ] = static_cast< T >( i );
            }

            for( size_t mapSizeB = 8; mapSizeB <= maxMapSize; mapSizeB *= 2 )
               for( size_t myOffB = dequeSize * ( mapSizeB - 1 ); myOffB < dequeSize * mapSizeB; ++myOffB )
               {
                  for( size_t mySizeB = dequeSize * ( mapSizeB - 1 ); mySizeB <= dequeSize * mapSizeB - myOffB % dequeSize; ++mySizeB )
                  {
                     std::deque< T > deque3;
                     T ***map3 = reinterpret_cast< T *** > ( &deque3 ) + 1;
                     size_t *mapSize3 = reinterpret_cast< size_t * >( &deque3 ) + 2;
                     size_t *myOff3 = reinterpret_cast< size_t * >( &deque3 ) + 3;
                     size_t *mySize3 = reinterpret_cast< size_t * >( &deque3 ) + 4;

                     deque< T > deque4;
                     T ***map4 = reinterpret_cast< T *** > ( &deque4 );
                     size_t *mapSize4 = reinterpret_cast< size_t * >( &deque4 ) + 1;
                     size_t *myOff4 = reinterpret_cast< size_t * >( &deque4 ) + 2;
                     size_t *mySize4 = reinterpret_cast< size_t * >( &deque4 ) + 3;

                     *mapSize3 = mapSizeB;
                     *mapSize4 = mapSizeB;
                     *map3 = new T*[ mapSizeB ]();
                     *map4 = new T*[ mapSizeB ]();
                     *myOff3 = myOffB;
                     *myOff4 = myOffB;
                     *mySize3 = mySizeB;
                     *mySize4 = mySizeB;

                     for( size_t block = myOffB / dequeSize; block <= ( myOffB + mySizeB - 1 ) / dequeSize; block++ )
                     {
                        ( *map3 )[ block % mapSizeB ] = new T[ dequeSize ];
                        ( *map4 )[ block % mapSizeB ] = new T[ dequeSize ];
                     }

                     for( size_t i = myOffB; i < myOffB + mySizeB; i++ )
                     {
                        size_t block = i % ( dequeSize * mapSizeB ) / dequeSize;
                        ( *map3 )[ block ][ i % dequeSize ] = static_cast< T >( i );
                        ( *map4 )[ block ][ i % dequeSize ] = static_cast< T >( i );
                     }

                     deque3 = deque1;
                     deque4 = deque2;

                     if( !equal( deque3, deque4 ) )
                        numErrors++;
                  }
               }
         }

         if( sizeof( T ) == 1 )
         {
            if( myOffA % 2 == 1 )
               cout << "There are " << numErrors << " errors\n";
         }
         else
            if( mapSizeA == maxMapSize && myOffA == 7 )
               cout << "There are " << numErrors << " errors\n";
      }

   cout << endl;
}

template< typename T >
void testAssignment21()
{
   size_t dequeSize = compDequeSize< T >(); // elements per block (a power of 2)

   const size_t maxMapSize = 32 * sizeof( T );
   size_t numErrors = 0;

   for( size_t mapSizeA = 8; mapSizeA <= maxMapSize; mapSizeA *= 2 )
      for( size_t myOffA = dequeSize * ( mapSizeA - 1 ); myOffA < dequeSize * mapSizeA; ++myOffA )
      {
         for( size_t mySizeA = 1; mySizeA <= 8; ++mySizeA )
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

            *mapSize1 = mapSizeA;
            *mapSize2 = mapSizeA;
            *map1 = new T*[ mapSizeA ]();
            *map2 = new T*[ *mapSize2 ]();
            *myOff1 = myOffA;
            *myOff2 = myOffA;
            *mySize1 = mySizeA;
            *mySize2 = mySizeA;

            for( size_t block = myOffA / dequeSize; block <= ( myOffA + mySizeA - 1 ) / dequeSize; block++ )
            {
               ( *map1 )[ block % mapSizeA ] = new T[ dequeSize ];
               ( *map2 )[ block % mapSizeA ] = new T[ dequeSize ];
            }

            for( size_t i = myOffA; i < myOffA + mySizeA; i++ )
            {
               size_t block = i % ( dequeSize * mapSizeA ) / dequeSize;
               ( *map1 )[ block ][ i % dequeSize ] = static_cast< T >( i );
               ( *map2 )[ block ][ i % dequeSize ] = static_cast< T >( i );
            }

            for( size_t mapSizeB = 8; mapSizeB <= maxMapSize; mapSizeB *= 2 )
               for( size_t myOffB = 0; myOffB < 8; ++myOffB )
               {
                  for( size_t mySizeB = 1; mySizeB <= 8; ++mySizeB )
                  {
                     std::deque< T > deque3;
                     T ***map3 = reinterpret_cast< T *** > ( &deque3 ) + 1;
                     size_t *mapSize3 = reinterpret_cast< size_t * >( &deque3 ) + 2;
                     size_t *myOff3 = reinterpret_cast< size_t * >( &deque3 ) + 3;
                     size_t *mySize3 = reinterpret_cast< size_t * >( &deque3 ) + 4;

                     deque< T > deque4;
                     T ***map4 = reinterpret_cast< T *** > ( &deque4 );
                     size_t *mapSize4 = reinterpret_cast< size_t * >( &deque4 ) + 1;
                     size_t *myOff4 = reinterpret_cast< size_t * >( &deque4 ) + 2;
                     size_t *mySize4 = reinterpret_cast< size_t * >( &deque4 ) + 3;

                     *mapSize3 = mapSizeB;
                     *mapSize4 = mapSizeB;
                     *map3 = new T*[ mapSizeB ]();
                     *map4 = new T*[ mapSizeB ]();
                     *myOff3 = myOffB;
                     *myOff4 = myOffB;
                     *mySize3 = mySizeB;
                     *mySize4 = mySizeB;

                     for( size_t block = myOffB / dequeSize; block <= ( myOffB + mySizeB - 1 ) / dequeSize; block++ )
                     {
                        ( *map3 )[ block % mapSizeB ] = new T[ dequeSize ];
                        ( *map4 )[ block % mapSizeB ] = new T[ dequeSize ];
                     }

                     for( size_t i = myOffB; i < myOffB + mySizeB; i++ )
                     {
                        size_t block = i % ( dequeSize * mapSizeB ) / dequeSize;
                        ( *map3 )[ block ][ i % dequeSize ] = static_cast< T >( i );
                        ( *map4 )[ block ][ i % dequeSize ] = static_cast< T >( i );
                     }

                     deque3 = deque1;
                     deque4 = deque2;

                     if( !equal( deque3, deque4 ) )
                        numErrors++;
                  }
               }
         }
      }

   cout << "There are " << numErrors << " errors\n\n";
}

template< typename T >
void testAssignment23()
{
   size_t dequeSize = compDequeSize< T >(); // elements per block (a power of 2)

   const size_t maxMapSize = 32 * sizeof( T );
   size_t numErrors = 0;

   for( size_t mapSizeA = 8; mapSizeA <= maxMapSize; mapSizeA *= 2 )
   {
      for( size_t myOffA = dequeSize * ( mapSizeA - 1 ); myOffA < dequeSize * mapSizeA; ++myOffA )
      {
         for( size_t mySizeA = 1; mySizeA <= 8; ++mySizeA )
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

            *mapSize1 = mapSizeA;
            *mapSize2 = mapSizeA;
            *map1 = new T * [ mapSizeA ]();
            *map2 = new T * [ *mapSize2 ]();
            *myOff1 = myOffA;
            *myOff2 = myOffA;
            *mySize1 = mySizeA;
            *mySize2 = mySizeA;

            for( size_t block = myOffA / dequeSize; block <= ( myOffA + mySizeA - 1 ) / dequeSize; block++ )
            {
               ( *map1 )[ block % mapSizeA ] = new T[ dequeSize ];
               ( *map2 )[ block % mapSizeA ] = new T[ dequeSize ];
            }

            for( size_t i = myOffA; i < myOffA + mySizeA; i++ )
            {
               size_t block = i % ( dequeSize * mapSizeA ) / dequeSize;
               ( *map1 )[ block ][ i % dequeSize ] = static_cast< T >( i );
               ( *map2 )[ block ][ i % dequeSize ] = static_cast< T >( i );
            }

            for( size_t mapSizeB = 8; mapSizeB <= maxMapSize; mapSizeB *= 2 )
               for( size_t myOffB = dequeSize * ( mapSizeB - 1 ); myOffB < dequeSize * mapSizeB; ++myOffB )
               {
                  for( size_t mySizeB = 1; mySizeB <= 8; ++mySizeB )
                  {
                     std::deque< T > deque3;
                     T ***map3 = reinterpret_cast< T *** > ( &deque3 ) + 1;
                     size_t *mapSize3 = reinterpret_cast< size_t * >( &deque3 ) + 2;
                     size_t *myOff3 = reinterpret_cast< size_t * >( &deque3 ) + 3;
                     size_t *mySize3 = reinterpret_cast< size_t * >( &deque3 ) + 4;

                     deque< T > deque4;
                     T ***map4 = reinterpret_cast< T *** > ( &deque4 );
                     size_t *mapSize4 = reinterpret_cast< size_t * >( &deque4 ) + 1;
                     size_t *myOff4 = reinterpret_cast< size_t * >( &deque4 ) + 2;
                     size_t *mySize4 = reinterpret_cast< size_t * >( &deque4 ) + 3;

                     *mapSize3 = mapSizeB;
                     *mapSize4 = mapSizeB;
                     *map3 = new T * [ mapSizeB ]();
                     *map4 = new T * [ mapSizeB ]();
                     *myOff3 = myOffB;
                     *myOff4 = myOffB;
                     *mySize3 = mySizeB;
                     *mySize4 = mySizeB;

                     for( size_t block = myOffB / dequeSize; block <= ( myOffB + mySizeB - 1 ) / dequeSize; block++ )
                     {
                        ( *map3 )[ block % mapSizeB ] = new T[ dequeSize ];
                        ( *map4 )[ block % mapSizeB ] = new T[ dequeSize ];
                     }

                     for( size_t i = myOffB; i < myOffB + mySizeB; i++ )
                     {
                        size_t block = i % ( dequeSize * mapSizeB ) / dequeSize;
                        ( *map3 )[ block ][ i % dequeSize ] = static_cast< T >( i );
                        ( *map4 )[ block ][ i % dequeSize ] = static_cast< T >( i );
                     }

                     deque3 = deque1;
                     deque4 = deque2;

                     if( !equal( deque3, deque4 ) )
                        numErrors++;
                  }
               }
         }
      }

      if( sizeof( T ) == 1 || mapSizeA == maxMapSize )
         cout << "There are " << numErrors << " errors\n";
   }

   cout << endl;
}

template< typename T >
void testAssignment25()
{
   size_t dequeSize = compDequeSize< T >(); // elements per block (a power of 2)

   const size_t maxMapSize = 8 * sizeof( T );
   size_t numErrors = 0;

   for( size_t mapSizeA = 8; mapSizeA <= maxMapSize; mapSizeA *= 2 )
   {
      for( size_t myOffA = dequeSize * ( mapSizeA - 1 ); myOffA < dequeSize * mapSizeA; ++myOffA )
      {
         for( size_t mySizeA = dequeSize * ( mapSizeA - 1 ); mySizeA <= dequeSize * mapSizeA - myOffA % dequeSize; ++mySizeA )
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

            *mapSize1 = mapSizeA;
            *mapSize2 = mapSizeA;
            *map1 = new T*[ mapSizeA ]();
            *map2 = new T*[ *mapSize2 ]();
            *myOff1 = myOffA;
            *myOff2 = myOffA;
            *mySize1 = mySizeA;
            *mySize2 = mySizeA;

            for( size_t block = myOffA / dequeSize; block <= ( myOffA + mySizeA - 1 ) / dequeSize; block++ )
            {
               ( *map1 )[ block % mapSizeA ] = new T[ dequeSize ];
               ( *map2 )[ block % mapSizeA ] = new T[ dequeSize ];
            }

            for( size_t i = myOffA; i < myOffA + mySizeA; i++ )
            {
               size_t block = i % ( dequeSize * mapSizeA ) / dequeSize;
               ( *map1 )[ block ][ i % dequeSize ] = static_cast< T >( i );
               ( *map2 )[ block ][ i % dequeSize ] = static_cast< T >( i );
            }

            for( size_t mapSizeB = 8; mapSizeB <= maxMapSize; mapSizeB *= 2 )
               for( size_t myOffB = 0; myOffB < 8; ++myOffB )
               {
                  for( size_t mySizeB = 1; mySizeB <= 8; ++mySizeB )
                  {
                     std::deque< T > deque3;
                     T ***map3 = reinterpret_cast< T *** > ( &deque3 ) + 1;
                     size_t *mapSize3 = reinterpret_cast< size_t * >( &deque3 ) + 2;
                     size_t *myOff3 = reinterpret_cast< size_t * >( &deque3 ) + 3;
                     size_t *mySize3 = reinterpret_cast< size_t * >( &deque3 ) + 4;

                     deque< T > deque4;
                     T ***map4 = reinterpret_cast< T *** > ( &deque4 );
                     size_t *mapSize4 = reinterpret_cast< size_t * >( &deque4 ) + 1;
                     size_t *myOff4 = reinterpret_cast< size_t * >( &deque4 ) + 2;
                     size_t *mySize4 = reinterpret_cast< size_t * >( &deque4 ) + 3;

                     *mapSize3 = mapSizeB;
                     *mapSize4 = mapSizeB;
                     *map3 = new T*[ mapSizeB ]();
                     *map4 = new T*[ mapSizeB ]();
                     *myOff3 = myOffB;
                     *myOff4 = myOffB;
                     *mySize3 = mySizeB;
                     *mySize4 = mySizeB;

                     for( size_t block = myOffB / dequeSize; block <= ( myOffB + mySizeB - 1 ) / dequeSize; block++ )
                     {
                        ( *map3 )[ block % mapSizeB ] = new T[ dequeSize ];
                        ( *map4 )[ block % mapSizeB ] = new T[ dequeSize ];
                     }

                     for( size_t i = myOffB; i < myOffB + mySizeB; i++ )
                     {
                        size_t block = i % ( dequeSize * mapSizeB ) / dequeSize;
                        ( *map3 )[ block ][ i % dequeSize ] = static_cast< T >( i );
                        ( *map4 )[ block ][ i % dequeSize ] = static_cast< T >( i );
                     }

                     deque3 = deque1;
                     deque4 = deque2;

                     if( !equal( deque3, deque4 ) )
                        numErrors++;
                  }
               }
         }

         if( ( sizeof( T ) == 1 || mapSizeA == maxMapSize ) && myOffA % 4 == 3 )
            cout << "There are " << numErrors << " errors\n";
      }
   }

   cout << endl;
}

template< typename T >
void testAssignment26()
{
   size_t dequeSize = compDequeSize< T >(); // elements per block (a power of 2)

   const size_t maxMapSize = 8 * sizeof( T );
   size_t numErrors = 0;

   for( size_t mapSizeA = 8; mapSizeA <= maxMapSize; mapSizeA *= 2 )
   {
      for( size_t myOffA = dequeSize * ( mapSizeA - 1 ); myOffA < dequeSize * mapSizeA; ++myOffA )
      {
         for( size_t mySizeA = dequeSize * ( mapSizeA - 1 ); mySizeA <= dequeSize * mapSizeA - myOffA % dequeSize; ++mySizeA )
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

            *mapSize1 = mapSizeA;
            *mapSize2 = mapSizeA;
            *map1 = new T*[ mapSizeA ]();
            *map2 = new T*[ *mapSize2 ]();
            *myOff1 = myOffA;
            *myOff2 = myOffA;
            *mySize1 = mySizeA;
            *mySize2 = mySizeA;

            for( size_t block = myOffA / dequeSize; block <= ( myOffA + mySizeA - 1 ) / dequeSize; block++ )
            {
               ( *map1 )[ block % mapSizeA ] = new T[ dequeSize ];
               ( *map2 )[ block % mapSizeA ] = new T[ dequeSize ];
            }

            for( size_t i = myOffA; i < myOffA + mySizeA; i++ )
            {
               size_t block = i % ( dequeSize * mapSizeA ) / dequeSize;
               ( *map1 )[ block ][ i % dequeSize ] = static_cast< T >( i );
               ( *map2 )[ block ][ i % dequeSize ] = static_cast< T >( i );
            }

            for( size_t mapSizeB = 8; mapSizeB <= maxMapSize; mapSizeB *= 2 )
               for( size_t myOffB = 0; myOffB < 8; ++myOffB )
               {
                  for( size_t mySizeB = dequeSize * ( mapSizeB - 1 ); mySizeB <= dequeSize * mapSizeB - myOffB % dequeSize; ++mySizeB )
                  {
                     std::deque< T > deque3;
                     T ***map3 = reinterpret_cast< T *** > ( &deque3 ) + 1;
                     size_t *mapSize3 = reinterpret_cast< size_t * >( &deque3 ) + 2;
                     size_t *myOff3 = reinterpret_cast< size_t * >( &deque3 ) + 3;
                     size_t *mySize3 = reinterpret_cast< size_t * >( &deque3 ) + 4;

                     deque< T > deque4;
                     T ***map4 = reinterpret_cast< T *** > ( &deque4 );
                     size_t *mapSize4 = reinterpret_cast< size_t * >( &deque4 ) + 1;
                     size_t *myOff4 = reinterpret_cast< size_t * >( &deque4 ) + 2;
                     size_t *mySize4 = reinterpret_cast< size_t * >( &deque4 ) + 3;

                     *mapSize3 = mapSizeB;
                     *mapSize4 = mapSizeB;
                     *map3 = new T*[ mapSizeB ]();
                     *map4 = new T*[ mapSizeB ]();
                     *myOff3 = myOffB;
                     *myOff4 = myOffB;
                     *mySize3 = mySizeB;
                     *mySize4 = mySizeB;

                     for( size_t block = myOffB / dequeSize; block <= ( myOffB + mySizeB - 1 ) / dequeSize; block++ )
                     {
                        ( *map3 )[ block % mapSizeB ] = new T[ dequeSize ];
                        ( *map4 )[ block % mapSizeB ] = new T[ dequeSize ];
                     }

                     for( size_t i = myOffB; i < myOffB + mySizeB; i++ )
                     {
                        size_t block = i % ( dequeSize * mapSizeB ) / dequeSize;
                        ( *map3 )[ block ][ i % dequeSize ] = static_cast< T >( i );
                        ( *map4 )[ block ][ i % dequeSize ] = static_cast< T >( i );
                     }

                     deque3 = deque1;
                     deque4 = deque2;

                     if( !equal( deque3, deque4 ) )
                        numErrors++;
                  }
               }
         }

         if( sizeof( T ) == 1 )
         {
            if( myOffA % 4 == 3 )
               cout << "There are " << numErrors << " errors\n";
         }
         else
            if( mapSizeA == maxMapSize && myOffA == dequeSize * mapSizeA - 1 )
               cout << "There are " << numErrors << " errors\n";
      }
   }

   cout << endl;
}

template< typename T >
void testAssignment27()
{
   size_t dequeSize = compDequeSize< T >(); // elements per block (a power of 2)

   const size_t maxMapSize = 8 * sizeof( T );
   size_t numErrors = 0;

   for( size_t mapSizeA = 8; mapSizeA <= maxMapSize; mapSizeA *= 2 )
      for( size_t myOffA = dequeSize * ( mapSizeA - 1 ); myOffA < dequeSize * mapSizeA; ++myOffA )
      {
         for( size_t mySizeA = dequeSize * ( mapSizeA - 1 ); mySizeA <= dequeSize * mapSizeA - myOffA % dequeSize; ++mySizeA )
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

            *mapSize1 = mapSizeA;
            *mapSize2 = mapSizeA;
            *map1 = new T*[ mapSizeA ]();
            *map2 = new T*[ *mapSize2 ]();
            *myOff1 = myOffA;
            *myOff2 = myOffA;
            *mySize1 = mySizeA;
            *mySize2 = mySizeA;

            for( size_t block = myOffA / dequeSize; block <= ( myOffA + mySizeA - 1 ) / dequeSize; block++ )
            {
               ( *map1 )[ block % mapSizeA ] = new T[ dequeSize ];
               ( *map2 )[ block % mapSizeA ] = new T[ dequeSize ];
            }

            for( size_t i = myOffA; i < myOffA + mySizeA; i++ )
            {
               size_t block = i % ( dequeSize * mapSizeA ) / dequeSize;
               ( *map1 )[ block ][ i % dequeSize ] = static_cast< T >( i );
               ( *map2 )[ block ][ i % dequeSize ] = static_cast< T >( i );
            }

            for( size_t mapSizeB = 8; mapSizeB <= maxMapSize; mapSizeB *= 2 )
               for( size_t myOffB = dequeSize * ( mapSizeB - 1 ); myOffB < dequeSize * mapSizeB; ++myOffB )
               {
                  for( size_t mySizeB = 1; mySizeB <= 8; ++mySizeB )
                  {
                     std::deque< T > deque3;
                     T ***map3 = reinterpret_cast< T *** > ( &deque3 ) + 1;
                     size_t *mapSize3 = reinterpret_cast< size_t * >( &deque3 ) + 2;
                     size_t *myOff3 = reinterpret_cast< size_t * >( &deque3 ) + 3;
                     size_t *mySize3 = reinterpret_cast< size_t * >( &deque3 ) + 4;

                     deque< T > deque4;
                     T ***map4 = reinterpret_cast< T *** > ( &deque4 );
                     size_t *mapSize4 = reinterpret_cast< size_t * >( &deque4 ) + 1;
                     size_t *myOff4 = reinterpret_cast< size_t * >( &deque4 ) + 2;
                     size_t *mySize4 = reinterpret_cast< size_t * >( &deque4 ) + 3;

                     *mapSize3 = mapSizeB;
                     *mapSize4 = mapSizeB;
                     *map3 = new T*[ mapSizeB ]();
                     *map4 = new T*[ mapSizeB ]();
                     *myOff3 = myOffB;
                     *myOff4 = myOffB;
                     *mySize3 = mySizeB;
                     *mySize4 = mySizeB;

                     for( size_t block = myOffB / dequeSize; block <= ( myOffB + mySizeB - 1 ) / dequeSize; block++ )
                     {
                        ( *map3 )[ block % mapSizeB ] = new T[ dequeSize ];
                        ( *map4 )[ block % mapSizeB ] = new T[ dequeSize ];
                     }

                     for( size_t i = myOffB; i < myOffB + mySizeB; i++ )
                     {
                        size_t block = i % ( dequeSize * mapSizeB ) / dequeSize;
                        ( *map3 )[ block ][ i % dequeSize ] = static_cast< T >( i );
                        ( *map4 )[ block ][ i % dequeSize ] = static_cast< T >( i );
                     }

                     deque3 = deque1;
                     deque4 = deque2;

                     if( !equal( deque3, deque4 ) )
                        numErrors++;
                  }
               }
         }

         if( sizeof( T ) == 1 )
         {
            if( myOffA % 2 == 1 )
               cout << "There are " << numErrors << " errors\n";
         }
         else if( sizeof( T ) == 2 )
         {
            if( myOffA == dequeSize * mapSizeA - 1 )
               cout << "There are " << numErrors << " errors\n";
         }
         else
            if( mapSizeA == maxMapSize && myOffA == dequeSize * mapSizeA - 1 )
               cout << "There are " << numErrors << " errors\n";
      }

   cout << endl;
}

template< typename T >
void testAssignment28()
{
   size_t dequeSize = compDequeSize< T >(); // elements per block (a power of 2)

   const size_t maxMapSize = 8 * sizeof( T );
   size_t numErrors = 0;

   for( size_t mapSizeA = 8; mapSizeA <= maxMapSize; mapSizeA *= 2 )
      for( size_t myOffA = dequeSize * ( mapSizeA - 1 ); myOffA < dequeSize * mapSizeA; ++myOffA )
      {
         for( size_t mySizeA = dequeSize * ( mapSizeA - 1 ); mySizeA <= dequeSize * mapSizeA - myOffA % dequeSize; ++mySizeA )
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

            *mapSize1 = mapSizeA;
            *mapSize2 = mapSizeA;
            *map1 = new T*[ mapSizeA ]();
            *map2 = new T*[ *mapSize2 ]();
            *myOff1 = myOffA;
            *myOff2 = myOffA;
            *mySize1 = mySizeA;
            *mySize2 = mySizeA;

            for( size_t block = myOffA / dequeSize; block <= ( myOffA + mySizeA - 1 ) / dequeSize; block++ )
            {
               ( *map1 )[ block % mapSizeA ] = new T[ dequeSize ];
               ( *map2 )[ block % mapSizeA ] = new T[ dequeSize ];
            }

            for( size_t i = myOffA; i < myOffA + mySizeA; i++ )
            {
               size_t block = i % ( dequeSize * mapSizeA ) / dequeSize;
               ( *map1 )[ block ][ i % dequeSize ] = static_cast< T >( i );
               ( *map2 )[ block ][ i % dequeSize ] = static_cast< T >( i );
            }

            for( size_t mapSizeB = 8; mapSizeB <= maxMapSize; mapSizeB *= 2 )
               for( size_t myOffB = dequeSize * ( mapSizeB - 1 ); myOffB < dequeSize * mapSizeB; ++myOffB )
               {
                  for( size_t mySizeB = dequeSize * ( mapSizeB - 1 ); mySizeB <= dequeSize * mapSizeB - myOffB % dequeSize; ++mySizeB )
                  {
                     std::deque< T > deque3;
                     T ***map3 = reinterpret_cast< T *** > ( &deque3 ) + 1;
                     size_t *mapSize3 = reinterpret_cast< size_t * >( &deque3 ) + 2;
                     size_t *myOff3 = reinterpret_cast< size_t * >( &deque3 ) + 3;
                     size_t *mySize3 = reinterpret_cast< size_t * >( &deque3 ) + 4;

                     deque< T > deque4;
                     T ***map4 = reinterpret_cast< T *** > ( &deque4 );
                     size_t *mapSize4 = reinterpret_cast< size_t * >( &deque4 ) + 1;
                     size_t *myOff4 = reinterpret_cast< size_t * >( &deque4 ) + 2;
                     size_t *mySize4 = reinterpret_cast< size_t * >( &deque4 ) + 3;

                     *mapSize3 = mapSizeB;
                     *mapSize4 = mapSizeB;
                     *map3 = new T*[ mapSizeB ]();
                     *map4 = new T*[ mapSizeB ]();
                     *myOff3 = myOffB;
                     *myOff4 = myOffB;
                     *mySize3 = mySizeB;
                     *mySize4 = mySizeB;

                     for( size_t block = myOffB / dequeSize; block <= ( myOffB + mySizeB - 1 ) / dequeSize; block++ )
                     {
                        ( *map3 )[ block % mapSizeB ] = new T[ dequeSize ];
                        ( *map4 )[ block % mapSizeB ] = new T[ dequeSize ];
                     }

                     for( size_t i = myOffB; i < myOffB + mySizeB; i++ )
                     {
                        size_t block = i % ( dequeSize * mapSizeB ) / dequeSize;
                        ( *map3 )[ block ][ i % dequeSize ] = static_cast< T >( i );
                        ( *map4 )[ block ][ i % dequeSize ] = static_cast< T >( i );
                     }

                     deque3 = deque1;
                     deque4 = deque2;

                     if( !equal( deque3, deque4 ) )
                        numErrors++;
                  }
               }
         }

         if( sizeof( T ) == 1 )
         {
            if( myOffA % 2 == 1 )
               cout << "There are " << numErrors << " errors\n";
         }
         else
            if( mapSizeA == maxMapSize && myOffA == dequeSize * mapSizeA - 1 )
               cout << "There are " << numErrors << " errors\n";
      }

   cout << endl;
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
   {
      row = ( i / dequeSize ) % mapSize1;
//      cout << "map1[ row ]  " << map1[ row ] << endl;
//      cout << "map2[ row ]  " << map2[ row ] << endl;
      if( map1[ row ] != nullptr && map2[ row ] == nullptr )
         return false;

      if( map1[ row ] == nullptr && map2[ row ] != nullptr )
         return false;

      if( map1[ row ] != nullptr && map2[ row ] != nullptr )
      {
         col = i % dequeSize;
//         cout << "map1[ row ][ col ]  " << map1[ row ][ col ] << endl;
//         cout << "map2[ row ][ col ]  " << map2[ row ][ col ] << endl;
         if( map1[ row ][ col ] != map2[ row ][ col ] )
            return false;
      }
   }

   return true;
}