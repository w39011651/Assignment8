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
void testAssignment3();

template< typename T >
void testAssignment4();

template< typename T >
void testAssignment5();


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
/**/
   testAssignment< char >();

   testAssignment< short >();

   testAssignment< long >();

   testAssignment< long long >();

   system( "pause" );
}

template< typename T >
void testAssignment()
{
   time_t t = time( nullptr );
/*
*/
   if( sizeof( T ) >= 4 )
      testAssignment1< T >(); // very long execution time

   testAssignment2< T >();

   testAssignment3< T >();

   if( sizeof( T ) >= 2 )
      testAssignment4< T >();

   if( sizeof( T ) >= 2 )
      testAssignment5< T >();

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
   cout << time( nullptr ) - t << " seconds\n\n";
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

   const size_t maxMapSize = 2 * sizeof( T );
   size_t numErrors = 0;
   for( size_t mapSizeA = 8; mapSizeA <= maxMapSize; mapSizeA *= 2 )
      for( size_t myOffA = 0; myOffA < dequeSize * mapSizeA; ++myOffA )
      {
         for( size_t mySizeA = 1; mySizeA <= dequeSize * mapSizeA - myOffA % dequeSize; ++mySizeA )
         {
            deque< T > deque1;
            T ***map1 = reinterpret_cast< T *** > ( &deque1 );
            size_t *mapSize1 = reinterpret_cast< size_t * >( &deque1 ) + 1;
            size_t *myOff1 = reinterpret_cast< size_t * >( &deque1 ) + 2;
            size_t *mySize1 = reinterpret_cast< size_t * >( &deque1 ) + 3;

            *mapSize1 = mapSizeA;
            *map1 = new T * [ mapSizeA ]();
            *myOff1 = myOffA;
            *mySize1 = mySizeA;

            for( size_t block = myOffA / dequeSize; block <= ( myOffA + mySizeA - 1 ) / dequeSize; block++ )
               ( *map1 )[ block % mapSizeA ] = new T[ dequeSize ];

            for( size_t i = myOffA; i < myOffA + mySizeA; i++ )
            {
               size_t block = i % ( dequeSize * mapSizeA ) / dequeSize;
               ( *map1 )[ block ][ i % dequeSize ] = static_cast< T >( i );
            }

            for( size_t mapSizeB = 8; mapSizeB <= maxMapSize; mapSizeB *= 2 )
               for( size_t myOffB = 0; myOffB < dequeSize * mapSizeB; ++myOffB )
               {
                  for( size_t mySizeB = 1; mySizeB <= dequeSize * mapSizeB - myOffB % dequeSize; ++mySizeB )
                  {
                     deque< T > deque2;
                     T ***map2 = reinterpret_cast< T *** > ( &deque2 );
                     size_t *mapSize2 = reinterpret_cast< size_t * >( &deque2 ) + 1;
                     size_t *myOff2 = reinterpret_cast< size_t * >( &deque2 ) + 2;
                     size_t *mySize2 = reinterpret_cast< size_t * >( &deque2 ) + 3;

                     *mapSize2 = mapSizeB;
                     *map2 = new T * [ mapSizeB ]();
                     *myOff2 = myOffB;
                     *mySize2 = mySizeB;

                     for( size_t block = myOffB / dequeSize; block <= ( myOffB + mySizeB - 1 ) / dequeSize; block++ )
                        ( *map2 )[ block % mapSizeB ] = new T[ dequeSize ];

                     for( size_t i = myOffB; i < myOffB + mySizeB; i++ )
                     {
                        size_t block = i % ( dequeSize * mapSizeB ) / dequeSize;
                        ( *map2 )[ block ][ i % dequeSize ] = static_cast< T >( i );
                     }

                     deque2 = deque1;

                     T ***map3 = reinterpret_cast< T *** > ( &deque2 );
                     size_t *mapSize3 = reinterpret_cast< size_t * >( &deque2 ) + 1;
                     size_t *myOff3 = reinterpret_cast< size_t * >( &deque2 ) + 2;
                     size_t *mySize3 = reinterpret_cast< size_t * >( &deque2 ) + 3;

                     if( *myOff3 != myOffB ) // Note that mySizeA != 0
                        numErrors++;

                     if( *mySize3 != mySizeA )
                        numErrors++;

                     if( mySizeA <= mySizeB )
                     {
                        if( *mapSize3 != mapSizeB )
                           numErrors++;

                        if( *map3 != *map2 )
                           numErrors++;
                     }

                     for( size_t block = myOffB / dequeSize; block <= ( myOffB + mySizeB - 1 ) / dequeSize; block++ )
                        if( ( *map3 )[ block % mapSizeB ] != ( *map2 )[ block % mapSizeB ] )
                           numErrors++;
                  }
               }
         }

         if( myOffA % 4 == 3 )
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
      for( size_t myOffA = 0; myOffA < 8; ++myOffA )
      {
         for( size_t mySizeA = 1; mySizeA <= 8; ++mySizeA )
         {
            deque< T > deque1;
            T ***map1 = reinterpret_cast< T *** > ( &deque1 );
            size_t *mapSize1 = reinterpret_cast< size_t * >( &deque1 ) + 1;
            size_t *myOff1 = reinterpret_cast< size_t * >( &deque1 ) + 2;
            size_t *mySize1 = reinterpret_cast< size_t * >( &deque1 ) + 3;

            *mapSize1 = mapSizeA;
            *map1 = new T * [ mapSizeA ]();
            *myOff1 = myOffA;
            *mySize1 = mySizeA;

            for( size_t block = myOffA / dequeSize; block <= ( myOffA + mySizeA - 1 ) / dequeSize; block++ )
               ( *map1 )[ block % mapSizeA ] = new T[ dequeSize ];

            for( size_t i = myOffA; i < myOffA + mySizeA; i++ )
            {
               size_t block = i % ( dequeSize * mapSizeA ) / dequeSize;
               ( *map1 )[ block ][ i % dequeSize ] = static_cast< T >( i );
            }

            for( size_t mapSizeB = 8; mapSizeB <= maxMapSize; mapSizeB *= 2 )
               for( size_t myOffB = 0; myOffB < dequeSize * mapSizeB; ++myOffB )
               {
                  for( size_t mySizeB = 1; mySizeB <= dequeSize * mapSizeB - myOffB % dequeSize; ++mySizeB )
                  {
                     deque< T > deque2;
                     T ***map2 = reinterpret_cast< T *** > ( &deque2 );
                     size_t *mapSize2 = reinterpret_cast< size_t * >( &deque2 ) + 1;
                     size_t *myOff2 = reinterpret_cast< size_t * >( &deque2 ) + 2;
                     size_t *mySize2 = reinterpret_cast< size_t * >( &deque2 ) + 3;

                     *mapSize2 = mapSizeB;
                     *map2 = new T * [ mapSizeB ]();
                     *myOff2 = myOffB;
                     *mySize2 = mySizeB;

                     for( size_t block = myOffB / dequeSize; block <= ( myOffB + mySizeB - 1 ) / dequeSize; block++ )
                        ( *map2 )[ block % mapSizeB ] = new T[ dequeSize ];

                     for( size_t i = myOffB; i < myOffB + mySizeB; i++ )
                     {
                        size_t block = i % ( dequeSize * mapSizeB ) / dequeSize;
                        ( *map2 )[ block ][ i % dequeSize ] = static_cast< T >( i );
                     }

                     deque2 = deque1;

                     T ***map3 = reinterpret_cast< T *** > ( &deque2 );
                     size_t *mapSize3 = reinterpret_cast< size_t * >( &deque2 ) + 1;
                     size_t *myOff3 = reinterpret_cast< size_t * >( &deque2 ) + 2;
                     size_t *mySize3 = reinterpret_cast< size_t * >( &deque2 ) + 3;

                     if( *myOff3 != myOffB ) // Note that mySizeA != 0
                        numErrors++;

                     if( *mySize3 != mySizeA )
                        numErrors++;

                     if( mySizeA <= mySizeB )
                     {
                        if( *mapSize3 != mapSizeB )
                           numErrors++;

                        if( *map3 != *map2 )
                           numErrors++;
                     }

                     for( size_t block = myOffB / dequeSize; block <= ( myOffB + mySizeB - 1 ) / dequeSize; block++ )
                        if( ( *map3 )[ block % mapSizeB ] != ( *map2 )[ block % mapSizeB ] )
                           numErrors++;
                  }
               }
         }

         if( sizeof( T ) == 1 )
         {
            if( myOffA % 2 == 1 )
               cout << "There are " << numErrors << " errors\n";
         }
         else if( sizeof( T ) <= 4 )
         {
            if( myOffA % 8 == 7 )
               cout << "There are " << numErrors << " errors\n";
         }
         else
            if( myOffA % 4 == 3 )
               cout << "There are " << numErrors << " errors\n";
      }

   cout << endl;
}

template< typename T >
void testAssignment3()
{
   size_t dequeSize = compDequeSize< T >(); // elements per block (a power of 2)

   const size_t maxMapSize = ( sizeof( T ) <= 2 ) ? 8 : 4 * sizeof( T );
   size_t numErrors = 0;
   for( size_t mapSizeA = 8; mapSizeA <= maxMapSize; mapSizeA *= 2 )
      for( size_t myOffA = 0; myOffA < dequeSize * mapSizeA; ++myOffA )
      {
         for( size_t mySizeA = 1; mySizeA <= dequeSize * mapSizeA - myOffA % dequeSize; ++mySizeA )
         {
            deque< T > deque1;
            T ***map1 = reinterpret_cast< T *** > ( &deque1 );
            size_t *mapSize1 = reinterpret_cast< size_t * >( &deque1 ) + 1;
            size_t *myOff1 = reinterpret_cast< size_t * >( &deque1 ) + 2;
            size_t *mySize1 = reinterpret_cast< size_t * >( &deque1 ) + 3;

            *mapSize1 = mapSizeA;
            *map1 = new T * [ mapSizeA ]();
            *myOff1 = myOffA;
            *mySize1 = mySizeA;

            for( size_t block = myOffA / dequeSize; block <= ( myOffA + mySizeA - 1 ) / dequeSize; block++ )
               ( *map1 )[ block % mapSizeA ] = new T[ dequeSize ];

            for( size_t i = myOffA; i < myOffA + mySizeA; i++ )
            {
               size_t block = i % ( dequeSize * mapSizeA ) / dequeSize;
               ( *map1 )[ block ][ i % dequeSize ] = static_cast< T >( i );
            }

            for( size_t mapSizeB = 8; mapSizeB <= maxMapSize; mapSizeB *= 2 )
               for( size_t myOffB = 0; myOffB < 8; ++myOffB )
               {
                  for( size_t mySizeB = 1; mySizeB <= 8; ++mySizeB )
                  {
                     deque< T > deque2;
                     T ***map2 = reinterpret_cast< T *** > ( &deque2 );
                     size_t *mapSize2 = reinterpret_cast< size_t * >( &deque2 ) + 1;
                     size_t *myOff2 = reinterpret_cast< size_t * >( &deque2 ) + 2;
                     size_t *mySize2 = reinterpret_cast< size_t * >( &deque2 ) + 3;

                     *mapSize2 = mapSizeB;
                     *map2 = new T * [ mapSizeB ]();
                     *myOff2 = myOffB;
                     *mySize2 = mySizeB;

                     for( size_t block = myOffB / dequeSize; block <= ( myOffB + mySizeB - 1 ) / dequeSize; block++ )
                        ( *map2 )[ block % mapSizeB ] = new T[ dequeSize ];

                     for( size_t i = myOffB; i < myOffB + mySizeB; i++ )
                     {
                        size_t block = i % ( dequeSize * mapSizeB ) / dequeSize;
                        ( *map2 )[ block ][ i % dequeSize ] = static_cast< T >( i );
                     }

                     deque2 = deque1;

                     T ***map3 = reinterpret_cast< T *** > ( &deque2 );
                     size_t *mapSize3 = reinterpret_cast< size_t * >( &deque2 ) + 1;
                     size_t *myOff3 = reinterpret_cast< size_t * >( &deque2 ) + 2;
                     size_t *mySize3 = reinterpret_cast< size_t * >( &deque2 ) + 3;

                     if( *myOff3 != myOffB ) // Note that mySizeA != 0
                        numErrors++;

                     if( *mySize3 != mySizeA )
                        numErrors++;

                     if( mySizeA <= mySizeB )
                     {
                        if( *mapSize3 != mapSizeB )
                           numErrors++;

                        if( *map3 != *map2 )
                           numErrors++;
                     }

                     for( size_t block = myOffB / dequeSize; block <= ( myOffB + mySizeB - 1 ) / dequeSize; block++ )
                        if( ( *map3 )[ block % mapSizeB ] != ( *map2 )[ block % mapSizeB ] )
                           numErrors++;
                  }
               }
         }

         if( sizeof( T ) == 1 )
         {
            if( myOffA % 16 == 15 )
               cout << "There are " << numErrors << " errors\n";
         }
         else if( sizeof( T ) == 2 )
         {
            if( mapSizeA == maxMapSize && myOffA == dequeSize * mapSizeA - 1 )
               cout << "There are " << numErrors << " errors\n";
         }
         else if( sizeof( T ) == 4 )
         {
            if( ( mapSizeA == maxMapSize && myOffA % 16 == 15 ) )
               cout << "There are " << numErrors << " errors\n";
         }
         else
            if( ( mapSizeA == maxMapSize / 2 && myOffA == dequeSize * mapSizeA - 1 ) ||
                ( mapSizeA == maxMapSize && myOffA % 8 == 7 ) )
               cout << "There are " << numErrors << " errors\n";
      }

   cout << endl;
}

template< typename T >
void testAssignment4()
{
   size_t dequeSize = compDequeSize< T >(); // elements per block (a power of 2)

   const size_t maxMapSize = 4 * sizeof( T );
   size_t numErrors = 0;

   for( size_t mapSizeA = 8; mapSizeA <= maxMapSize; mapSizeA *= 2 )
      for( size_t myOffA = dequeSize * ( mapSizeA - 1 ); myOffA < dequeSize * mapSizeA; ++myOffA )
      {
         for( size_t mySizeA = dequeSize * ( mapSizeA - 1 ); mySizeA <= dequeSize * mapSizeA - myOffA % dequeSize; ++mySizeA )
         {
            deque< T > deque1;
            T ***map1 = reinterpret_cast< T *** > ( &deque1 );
            size_t *mapSize1 = reinterpret_cast< size_t * >( &deque1 ) + 1;
            size_t *myOff1 = reinterpret_cast< size_t * >( &deque1 ) + 2;
            size_t *mySize1 = reinterpret_cast< size_t * >( &deque1 ) + 3;

            *mapSize1 = mapSizeA;
            *map1 = new T * [ mapSizeA ]();
            *myOff1 = myOffA;
            *mySize1 = mySizeA;

            for( size_t block = myOffA / dequeSize; block <= ( myOffA + mySizeA - 1 ) / dequeSize; block++ )
               ( *map1 )[ block % mapSizeA ] = new T[ dequeSize ];

            for( size_t i = myOffA; i < myOffA + mySizeA; i++ )
            {
               size_t block = i % ( dequeSize * mapSizeA ) / dequeSize;
               ( *map1 )[ block ][ i % dequeSize ] = static_cast< T >( i );
            }

            for( size_t mapSizeB = 8; mapSizeB <= maxMapSize; mapSizeB *= 2 )
               for( size_t myOffB = 0; myOffB < dequeSize * mapSizeB; ++myOffB )
               {
                  for( size_t mySizeB = 1; mySizeB <= dequeSize * mapSizeB - myOffB % dequeSize; ++mySizeB )
                  {
                     deque< T > deque2;
                     T ***map2 = reinterpret_cast< T *** > ( &deque2 );
                     size_t *mapSize2 = reinterpret_cast< size_t * >( &deque2 ) + 1;
                     size_t *myOff2 = reinterpret_cast< size_t * >( &deque2 ) + 2;
                     size_t *mySize2 = reinterpret_cast< size_t * >( &deque2 ) + 3;

                     *mapSize2 = mapSizeB;
                     *map2 = new T * [ mapSizeB ]();
                     *myOff2 = myOffB;
                     *mySize2 = mySizeB;

                     for( size_t block = myOffB / dequeSize; block <= ( myOffB + mySizeB - 1 ) / dequeSize; block++ )
                        ( *map2 )[ block % mapSizeB ] = new T[ dequeSize ];

                     for( size_t i = myOffB; i < myOffB + mySizeB; i++ )
                     {
                        size_t block = i % ( dequeSize * mapSizeB ) / dequeSize;
                        ( *map2 )[ block ][ i % dequeSize ] = static_cast< T >( i );
                     }

                     deque2 = deque1;

                     T ***map3 = reinterpret_cast< T *** > ( &deque2 );
                     size_t *mapSize3 = reinterpret_cast< size_t * >( &deque2 ) + 1;
                     size_t *myOff3 = reinterpret_cast< size_t * >( &deque2 ) + 2;
                     size_t *mySize3 = reinterpret_cast< size_t * >( &deque2 ) + 3;

                     if( *myOff3 != myOffB ) // Note that mySizeA != 0
                        numErrors++;

                     if( *mySize3 != mySizeA )
                        numErrors++;

                     if( mySizeA <= mySizeB )
                     {
                        if( *mapSize3 != mapSizeB )
                           numErrors++;

                        if( *map3 != *map2 )
                           numErrors++;
                     }

                     for( size_t block = myOffB / dequeSize; block <= ( myOffB + mySizeB - 1 ) / dequeSize; block++ )
                        if( ( *map3 )[ block % mapSizeB ] != ( *map2 )[ block % mapSizeB ] )
                           numErrors++;
                  }
               }
         }

         if( mapSizeA == maxMapSize && myOffA % 4 == 3 )
            cout << "There are " << numErrors << " errors\n";
      }

   cout << endl;
}

template< typename T >
void testAssignment5()
{
   size_t dequeSize = compDequeSize< T >(); // elements per block (a power of 2)

   const size_t maxMapSize = 4 * sizeof( T );
   size_t numErrors = 0;
   for( size_t mapSizeA = 8; mapSizeA <= maxMapSize; mapSizeA *= 2 )
      for( size_t myOffA = 0; myOffA < dequeSize * mapSizeA; ++myOffA )
      {
         for( size_t mySizeA = 1; mySizeA <= dequeSize * mapSizeA - myOffA % dequeSize; ++mySizeA )
         {
            deque< T > deque1;
            T ***map1 = reinterpret_cast< T *** > ( &deque1 );
            size_t *mapSize1 = reinterpret_cast< size_t * >( &deque1 ) + 1;
            size_t *myOff1 = reinterpret_cast< size_t * >( &deque1 ) + 2;
            size_t *mySize1 = reinterpret_cast< size_t * >( &deque1 ) + 3;

            *mapSize1 = mapSizeA;
            *map1 = new T * [ mapSizeA ]();
            *myOff1 = myOffA;
            *mySize1 = mySizeA;

            for( size_t block = myOffA / dequeSize; block <= ( myOffA + mySizeA - 1 ) / dequeSize; block++ )
               ( *map1 )[ block % mapSizeA ] = new T[ dequeSize ];

            for( size_t i = myOffA; i < myOffA + mySizeA; i++ )
            {
               size_t block = i % ( dequeSize * mapSizeA ) / dequeSize;
               ( *map1 )[ block ][ i % dequeSize ] = static_cast< T >( i );
            }

            for( size_t mapSizeB = 8; mapSizeB <= maxMapSize; mapSizeB *= 2 )
               for( size_t myOffB = dequeSize * ( mapSizeB - 1 ); myOffB < dequeSize * mapSizeB; ++myOffB )
               {
                  for( size_t mySizeB = dequeSize * ( mapSizeB - 1 ); mySizeB <= dequeSize * mapSizeB - myOffB % dequeSize; ++mySizeB )
                  {
                     deque< T > deque2;
                     T ***map2 = reinterpret_cast< T *** > ( &deque2 );
                     size_t *mapSize2 = reinterpret_cast< size_t * >( &deque2 ) + 1;
                     size_t *myOff2 = reinterpret_cast< size_t * >( &deque2 ) + 2;
                     size_t *mySize2 = reinterpret_cast< size_t * >( &deque2 ) + 3;

                     *mapSize2 = mapSizeB;
                     *map2 = new T * [ mapSizeB ]();
                     *myOff2 = myOffB;
                     *mySize2 = mySizeB;

                     for( size_t block = myOffB / dequeSize; block <= ( myOffB + mySizeB - 1 ) / dequeSize; block++ )
                        ( *map2 )[ block % mapSizeB ] = new T[ dequeSize ];

                     for( size_t i = myOffB; i < myOffB + mySizeB; i++ )
                     {
                        size_t block = i % ( dequeSize * mapSizeB ) / dequeSize;
                        ( *map2 )[ block ][ i % dequeSize ] = static_cast< T >( i );
                     }

                     deque2 = deque1;

                     T ***map3 = reinterpret_cast< T *** > ( &deque2 );
                     size_t *mapSize3 = reinterpret_cast< size_t * >( &deque2 ) + 1;
                     size_t *myOff3 = reinterpret_cast< size_t * >( &deque2 ) + 2;
                     size_t *mySize3 = reinterpret_cast< size_t * >( &deque2 ) + 3;

                     if( *myOff3 != myOffB ) // Note that mySizeA != 0
                        numErrors++;

                     if( *mySize3 != mySizeA )
                        numErrors++;

                     if( mySizeA <= mySizeB )
                     {
                        if( *mapSize3 != mapSizeB )
                           numErrors++;

                        if( *map3 != *map2 )
                           numErrors++;
                     }

                     for( size_t block = myOffB / dequeSize; block <= ( myOffB + mySizeB - 1 ) / dequeSize; block++ )
                        if( ( *map3 )[ block % mapSizeB ] != ( *map2 )[ block % mapSizeB ] )
                           numErrors++;
                  }
               }
         }

         if( sizeof( T ) == 2 )
         {
            if( ( mapSizeA == maxMapSize && myOffA % 32 == 31 ) )
               cout << "There are " << numErrors << " errors\n";
         }
         else
            if( ( mapSizeA == maxMapSize && myOffA == dequeSize * mapSizeA - 1 ) )
               cout << "There are " << numErrors << " errors\n";
      }

   cout << endl;
}

template< typename T >
void testAssignment11()
{
   size_t dequeSize = compDequeSize< T >(); // elements per block (a power of 2)

   const size_t maxMapSize = 256;
   size_t numErrors = 0;

   for( size_t mapSizeA = 8; mapSizeA <= maxMapSize; mapSizeA *= 2 )
   {
      for( size_t myOffA = 0; myOffA < 8; ++myOffA )
      {
         for( size_t mySizeA = 1; mySizeA <= 8; ++mySizeA )
         {
            deque< T > deque1;
            T ***map1 = reinterpret_cast< T *** > ( &deque1 );
            size_t *mapSize1 = reinterpret_cast< size_t * >( &deque1 ) + 1;
            size_t *myOff1 = reinterpret_cast< size_t * >( &deque1 ) + 2;
            size_t *mySize1 = reinterpret_cast< size_t * >( &deque1 ) + 3;

            *mapSize1 = mapSizeA;
            *map1 = new T * [ mapSizeA ]();
            *myOff1 = myOffA;
            *mySize1 = mySizeA;

            for( size_t block = myOffA / dequeSize; block <= ( myOffA + mySizeA - 1 ) / dequeSize; block++ )
               ( *map1 )[ block % mapSizeA ] = new T[ dequeSize ];

            for( size_t i = myOffA; i < myOffA + mySizeA; i++ )
            {
               size_t block = i % ( dequeSize * mapSizeA ) / dequeSize;
               ( *map1 )[ block ][ i % dequeSize ] = static_cast< T >( i );
            }

            for( size_t mapSizeB = 8; mapSizeB <= maxMapSize; mapSizeB *= 2 )
               for( size_t myOffB = 0; myOffB < 8; ++myOffB )
               {
                  for( size_t mySizeB = 1; mySizeB <= 8; ++mySizeB )
                  {
                     deque< T > deque2;
                     T ***map2 = reinterpret_cast< T *** > ( &deque2 );
                     size_t *mapSize2 = reinterpret_cast< size_t * >( &deque2 ) + 1;
                     size_t *myOff2 = reinterpret_cast< size_t * >( &deque2 ) + 2;
                     size_t *mySize2 = reinterpret_cast< size_t * >( &deque2 ) + 3;

                     *mapSize2 = mapSizeB;
                     *map2 = new T * [ mapSizeB ]();
                     *myOff2 = myOffB;
                     *mySize2 = mySizeB;

                     for( size_t block = myOffB / dequeSize; block <= ( myOffB + mySizeB - 1 ) / dequeSize; block++ )
                        ( *map2 )[ block % mapSizeB ] = new T[ dequeSize ];

                     for( size_t i = myOffB; i < myOffB + mySizeB; i++ )
                     {
                        size_t block = i % ( dequeSize * mapSizeB ) / dequeSize;
                        ( *map2 )[ block ][ i % dequeSize ] = static_cast< T >( i );
                     }

                     deque2 = deque1;

                     T ***map3 = reinterpret_cast< T *** > ( &deque2 );
                     size_t *mapSize3 = reinterpret_cast< size_t * >( &deque2 ) + 1;
                     size_t *myOff3 = reinterpret_cast< size_t * >( &deque2 ) + 2;
                     size_t *mySize3 = reinterpret_cast< size_t * >( &deque2 ) + 3;

                     if( *myOff3 != myOffB ) // Note that mySizeA != 0
                        numErrors++;

                     if( *mySize3 != mySizeA )
                        numErrors++;

                     if( mySizeA <= mySizeB )
                     {
                        if( *mapSize3 != mapSizeB )
                           numErrors++;

                        if( *map3 != *map2 )
                           numErrors++;
                     }

                     for( size_t block = myOffB / dequeSize; block <= ( myOffB + mySizeB - 1 ) / dequeSize; block++ )
                        if( ( *map3 )[ block % mapSizeB ] != ( *map2 )[ block % mapSizeB ] )
                           numErrors++;
                  }
               }
         }
      }
   }

   cout << "There are " << numErrors << " errors\n\n";
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
            deque< T > deque1;
            T ***map1 = reinterpret_cast< T *** > ( &deque1 );
            size_t *mapSize1 = reinterpret_cast< size_t * >( &deque1 ) + 1;
            size_t *myOff1 = reinterpret_cast< size_t * >( &deque1 ) + 2;
            size_t *mySize1 = reinterpret_cast< size_t * >( &deque1 ) + 3;

            *mapSize1 = mapSizeA;
            *map1 = new T * [ mapSizeA ]();
            *myOff1 = myOffA;
            *mySize1 = mySizeA;

            for( size_t block = myOffA / dequeSize; block <= ( myOffA + mySizeA - 1 ) / dequeSize; block++ )
               ( *map1 )[ block % mapSizeA ] = new T[ dequeSize ];

            for( size_t i = myOffA; i < myOffA + mySizeA; i++ )
            {
               size_t block = i % ( dequeSize * mapSizeA ) / dequeSize;
               ( *map1 )[ block ][ i % dequeSize ] = static_cast< T >( i );
            }

            for( size_t mapSizeB = 8; mapSizeB <= maxMapSize; mapSizeB *= 2 )
               for( size_t myOffB = dequeSize * ( mapSizeB - 2 ); myOffB < dequeSize * mapSizeB; ++myOffB )
               {
                  for( size_t mySizeB = 1; mySizeB <= 8; ++mySizeB )
                  {
                     deque< T > deque2;
                     T ***map2 = reinterpret_cast< T *** > ( &deque2 );
                     size_t *mapSize2 = reinterpret_cast< size_t * >( &deque2 ) + 1;
                     size_t *myOff2 = reinterpret_cast< size_t * >( &deque2 ) + 2;
                     size_t *mySize2 = reinterpret_cast< size_t * >( &deque2 ) + 3;

                     *mapSize2 = mapSizeB;
                     *map2 = new T * [ mapSizeB ]();
                     *myOff2 = myOffB;
                     *mySize2 = mySizeB;

                     for( size_t block = myOffB / dequeSize; block <= ( myOffB + mySizeB - 1 ) / dequeSize; block++ )
                        ( *map2 )[ block % mapSizeB ] = new T[ dequeSize ];

                     for( size_t i = myOffB; i < myOffB + mySizeB; i++ )
                     {
                        size_t block = i % ( dequeSize * mapSizeB ) / dequeSize;
                        ( *map2 )[ block ][ i % dequeSize ] = static_cast< T >( i );
                     }

                     deque2 = deque1;

                     T ***map3 = reinterpret_cast< T *** > ( &deque2 );
                     size_t *mapSize3 = reinterpret_cast< size_t * >( &deque2 ) + 1;
                     size_t *myOff3 = reinterpret_cast< size_t * >( &deque2 ) + 2;
                     size_t *mySize3 = reinterpret_cast< size_t * >( &deque2 ) + 3;

                     if( *myOff3 != myOffB ) // Note that mySizeA != 0
                        numErrors++;

                     if( *mySize3 != mySizeA )
                        numErrors++;

                     if( mySizeA <= mySizeB )
                     {
                        if( *mapSize3 != mapSizeB )
                           numErrors++;

                        if( *map3 != *map2 )
                           numErrors++;
                     }

                     for( size_t block = myOffB / dequeSize; block <= ( myOffB + mySizeB - 1 ) / dequeSize; block++ )
                        if( ( *map3 )[ block % mapSizeB ] != ( *map2 )[ block % mapSizeB ] )
                           numErrors++;
                  }
               }
         }
      }
   }

   cout << "There are " << numErrors << " errors\n\n";
}

template< typename T >
void testAssignment15()
{
   size_t dequeSize = compDequeSize< T >(); // elements per block (a power of 2)

   const size_t maxMapSize = 32 * sizeof( T );
   size_t numErrors = 0;

   for( size_t mapSizeA = 8; mapSizeA <= maxMapSize; mapSizeA *= 2 )
      for( size_t myOffA = 0; myOffA < 8; ++myOffA )
      {
         for( size_t mySizeA = dequeSize * ( mapSizeA - 1 ); mySizeA <= dequeSize * mapSizeA - myOffA % dequeSize; ++mySizeA )
         {
            deque< T > deque1;
            T ***map1 = reinterpret_cast< T *** > ( &deque1 );
            size_t *mapSize1 = reinterpret_cast< size_t * >( &deque1 ) + 1;
            size_t *myOff1 = reinterpret_cast< size_t * >( &deque1 ) + 2;
            size_t *mySize1 = reinterpret_cast< size_t * >( &deque1 ) + 3;

            *mapSize1 = mapSizeA;
            *map1 = new T * [ mapSizeA ]();
            *myOff1 = myOffA;
            *mySize1 = mySizeA;

            for( size_t block = myOffA / dequeSize; block <= ( myOffA + mySizeA - 1 ) / dequeSize; block++ )
               ( *map1 )[ block % mapSizeA ] = new T[ dequeSize ];

            for( size_t i = myOffA; i < myOffA + mySizeA; i++ )
            {
               size_t block = i % ( dequeSize * mapSizeA ) / dequeSize;
               ( *map1 )[ block ][ i % dequeSize ] = static_cast< T >( i );
            }

            for( size_t mapSizeB = 8; mapSizeB <= maxMapSize; mapSizeB *= 2 )
               for( size_t myOffB = 0; myOffB < 8; ++myOffB )
               {
                 for( size_t mySizeB = 1; mySizeB <= 8; ++mySizeB )
                  {
                    deque< T > deque2;
                    T ***map2 = reinterpret_cast< T *** > ( &deque2 );
                    size_t *mapSize2 = reinterpret_cast< size_t * >( &deque2 ) + 1;
                    size_t *myOff2 = reinterpret_cast< size_t * >( &deque2 ) + 2;
                    size_t *mySize2 = reinterpret_cast< size_t * >( &deque2 ) + 3;

                    *mapSize2 = mapSizeB;
                    *map2 = new T * [ mapSizeB ]();
                    *myOff2 = myOffB;
                    *mySize2 = mySizeB;

                    for( size_t block = myOffB / dequeSize; block <= ( myOffB + mySizeB - 1 ) / dequeSize; block++ )
                       ( *map2 )[ block % mapSizeB ] = new T[ dequeSize ];

                    for( size_t i = myOffB; i < myOffB + mySizeB; i++ )
                    {
                       size_t block = i % ( dequeSize * mapSizeB ) / dequeSize;
                       ( *map2 )[ block ][ i % dequeSize ] = static_cast< T >( i );
                    }

                    deque2 = deque1;

                    T ***map3 = reinterpret_cast< T *** > ( &deque2 );
                    size_t *mapSize3 = reinterpret_cast< size_t * >( &deque2 ) + 1;
                    size_t *myOff3 = reinterpret_cast< size_t * >( &deque2 ) + 2;
                    size_t *mySize3 = reinterpret_cast< size_t * >( &deque2 ) + 3;

                    if( *myOff3 != myOffB ) // Note that mySizeA != 0
                       numErrors++;

                    if( *mySize3 != mySizeA )
                       numErrors++;

                    if( mySizeA <= mySizeB )
                    {
                       if( *mapSize3 != mapSizeB )
                          numErrors++;

                       if( *map3 != *map2 )
                          numErrors++;
                    }

                    for( size_t block = myOffB / dequeSize; block <= ( myOffB + mySizeB - 1 ) / dequeSize; block++ )
                       if( ( *map3 )[ block % mapSizeB ] != ( *map2 )[ block % mapSizeB ] )
                          numErrors++;
                 }
               }
         }

         if( sizeof( T ) == 1 )
         {
            if( ( mapSizeA < maxMapSize && myOffA % 8 == 7 ) ||
                ( mapSizeA == maxMapSize && myOffA % 4 == 3 ) )
               cout << "There are " << numErrors << " errors\n";
         }
         else
            if( mapSizeA == maxMapSize && myOffA % 8 == 7 )
               cout << "There are " << numErrors << " errors\n";
      }

   cout << endl;
}

template< typename T >
void testAssignment16()
{
   size_t dequeSize = compDequeSize< T >(); // elements per block (a power of 2)

   const size_t maxMapSize = 32 * sizeof( T );
   size_t numErrors = 0;

   for( size_t mapSizeA = 8; mapSizeA <= maxMapSize; mapSizeA *= 2 )
      for( size_t myOffA = 0; myOffA < 8; ++myOffA )
      {
         for( size_t mySizeA = dequeSize * ( mapSizeA - 1 ); mySizeA <= dequeSize * mapSizeA - myOffA % dequeSize; ++mySizeA )
         {
            deque< T > deque1;
            T ***map1 = reinterpret_cast< T *** > ( &deque1 );
            size_t *mapSize1 = reinterpret_cast< size_t * >( &deque1 ) + 1;
            size_t *myOff1 = reinterpret_cast< size_t * >( &deque1 ) + 2;
            size_t *mySize1 = reinterpret_cast< size_t * >( &deque1 ) + 3;

            *mapSize1 = mapSizeA;
            *map1 = new T * [ mapSizeA ]();
            *myOff1 = myOffA;
            *mySize1 = mySizeA;

            for( size_t block = myOffA / dequeSize; block <= ( myOffA + mySizeA - 1 ) / dequeSize; block++ )
               ( *map1 )[ block % mapSizeA ] = new T[ dequeSize ];

            for( size_t i = myOffA; i < myOffA + mySizeA; i++ )
            {
               size_t block = i % ( dequeSize * mapSizeA ) / dequeSize;
               ( *map1 )[ block ][ i % dequeSize ] = static_cast< T >( i );
            }

            for( size_t mapSizeB = 8; mapSizeB <= maxMapSize; mapSizeB *= 2 )
               for( size_t myOffB = 0; myOffB < 8; ++myOffB )
               {
                  for( size_t mySizeB = dequeSize * ( mapSizeB - 1 ); mySizeB <= dequeSize * mapSizeB - myOffB % dequeSize; ++mySizeB )
                  {
                     deque< T > deque2;
                     T ***map2 = reinterpret_cast< T *** > ( &deque2 );
                     size_t *mapSize2 = reinterpret_cast< size_t * >( &deque2 ) + 1;
                     size_t *myOff2 = reinterpret_cast< size_t * >( &deque2 ) + 2;
                     size_t *mySize2 = reinterpret_cast< size_t * >( &deque2 ) + 3;

                     *mapSize2 = mapSizeB;
                     *map2 = new T * [ mapSizeB ]();
                     *myOff2 = myOffB;
                     *mySize2 = mySizeB;

                     for( size_t block = myOffB / dequeSize; block <= ( myOffB + mySizeB - 1 ) / dequeSize; block++ )
                        ( *map2 )[ block % mapSizeB ] = new T[ dequeSize ];

                     for( size_t i = myOffB; i < myOffB + mySizeB; i++ )
                     {
                        size_t block = i % ( dequeSize * mapSizeB ) / dequeSize;
                        ( *map2 )[ block ][ i % dequeSize ] = static_cast< T >( i );
                     }

                     deque2 = deque1;

                     T ***map3 = reinterpret_cast< T *** > ( &deque2 );
                     size_t *mapSize3 = reinterpret_cast< size_t * >( &deque2 ) + 1;
                     size_t *myOff3 = reinterpret_cast< size_t * >( &deque2 ) + 2;
                     size_t *mySize3 = reinterpret_cast< size_t * >( &deque2 ) + 3;

                     if( *myOff3 != myOffB ) // Note that mySizeA != 0
                        numErrors++;

                     if( *mySize3 != mySizeA )
                        numErrors++;

                     if( mySizeA <= mySizeB )
                     {
                        if( *mapSize3 != mapSizeB )
                           numErrors++;

                        if( *map3 != *map2 )
                           numErrors++;
                     }

                     for( size_t block = myOffB / dequeSize; block <= ( myOffB + mySizeB - 1 ) / dequeSize; block++ )
                        if( ( *map3 )[ block % mapSizeB ] != ( *map2 )[ block % mapSizeB ] )
                           numErrors++;
                  }
               }
         }

         if( sizeof( T ) == 1 )
         {
            if( ( mapSizeA < maxMapSize && myOffA % 8 == 7 ) ||
                ( mapSizeA == maxMapSize && myOffA % 4 == 3 ) )
               cout << "There are " << numErrors << " errors\n";
         }
         else
            if( mapSizeA == maxMapSize && myOffA % 8 == 7 )
               cout << "There are " << numErrors << " errors\n";
      }

   cout << endl;
}

template< typename T >
void testAssignment17()
{
   size_t dequeSize = compDequeSize< T >(); // elements per block (a power of 2)

   const size_t maxMapSize = 32 * sizeof( T );
   size_t numErrors = 0;

   for( size_t mapSizeA = 8; mapSizeA <= maxMapSize; mapSizeA *= 2 )
      for( size_t myOffA = 0; myOffA < 8; ++myOffA )
      {
         for( size_t mySizeA = dequeSize * ( mapSizeA - 1 ); mySizeA <= dequeSize * mapSizeA - myOffA % dequeSize; ++mySizeA )
         {
            deque< T > deque1;
            T ***map1 = reinterpret_cast< T *** > ( &deque1 );
            size_t *mapSize1 = reinterpret_cast< size_t * >( &deque1 ) + 1;
            size_t *myOff1 = reinterpret_cast< size_t * >( &deque1 ) + 2;
            size_t *mySize1 = reinterpret_cast< size_t * >( &deque1 ) + 3;

            *mapSize1 = mapSizeA;
            *map1 = new T * [ mapSizeA ]();
            *myOff1 = myOffA;
            *mySize1 = mySizeA;

            for( size_t block = myOffA / dequeSize; block <= ( myOffA + mySizeA - 1 ) / dequeSize; block++ )
               ( *map1 )[ block % mapSizeA ] = new T[ dequeSize ];

            for( size_t i = myOffA; i < myOffA + mySizeA; i++ )
            {
               size_t block = i % ( dequeSize * mapSizeA ) / dequeSize;
               ( *map1 )[ block ][ i % dequeSize ] = static_cast< T >( i );
            }

            for( size_t mapSizeB = 8; mapSizeB <= maxMapSize; mapSizeB *= 2 )
               for( size_t myOffB = dequeSize * ( mapSizeB - 1 ); myOffB < dequeSize * mapSizeB; ++myOffB )
               {
                  for( size_t mySizeB = 1; mySizeB <= 8; ++mySizeB )
                  {
                     deque< T > deque2;
                     T ***map2 = reinterpret_cast< T *** > ( &deque2 );
                     size_t *mapSize2 = reinterpret_cast< size_t * >( &deque2 ) + 1;
                     size_t *myOff2 = reinterpret_cast< size_t * >( &deque2 ) + 2;
                     size_t *mySize2 = reinterpret_cast< size_t * >( &deque2 ) + 3;

                     *mapSize2 = mapSizeB;
                     *map2 = new T * [ mapSizeB ]();
                     *myOff2 = myOffB;
                     *mySize2 = mySizeB;

                     for( size_t block = myOffB / dequeSize; block <= ( myOffB + mySizeB - 1 ) / dequeSize; block++ )
                        ( *map2 )[ block % mapSizeB ] = new T[ dequeSize ];

                     for( size_t i = myOffB; i < myOffB + mySizeB; i++ )
                     {
                        size_t block = i % ( dequeSize * mapSizeB ) / dequeSize;
                        ( *map2 )[ block ][ i % dequeSize ] = static_cast< T >( i );
                     }

                     deque2 = deque1;

                     T ***map3 = reinterpret_cast< T *** > ( &deque2 );
                     size_t *mapSize3 = reinterpret_cast< size_t * >( &deque2 ) + 1;
                     size_t *myOff3 = reinterpret_cast< size_t * >( &deque2 ) + 2;
                     size_t *mySize3 = reinterpret_cast< size_t * >( &deque2 ) + 3;

                     if( *myOff3 != myOffB ) // Note that mySizeA != 0
                        numErrors++;

                     if( *mySize3 != mySizeA )
                        numErrors++;

                     if( mySizeA <= mySizeB )
                     {
                        if( *mapSize3 != mapSizeB )
                           numErrors++;

                        if( *map3 != *map2 )
                           numErrors++;
                     }

                     for( size_t block = myOffB / dequeSize; block <= ( myOffB + mySizeB - 1 ) / dequeSize; block++ )
                        if( ( *map3 )[ block % mapSizeB ] != ( *map2 )[ block % mapSizeB ] )
                           numErrors++;
                  }
               }
         }

         if( sizeof( T ) == 1 )
         {
            if( ( mapSizeA < maxMapSize && myOffA % 8 == 7 ) ||
                ( mapSizeA == maxMapSize && myOffA % 4 == 3 ) )
               cout << "There are " << numErrors << " errors\n";
         }
         else if( sizeof( T ) == 2 )
         {
            if( mapSizeA >= maxMapSize / 2 && myOffA == 7 )
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

   const size_t maxMapSize = 32 * sizeof( T );
   size_t numErrors = 0;

   for( size_t mapSizeA = 8; mapSizeA <= maxMapSize; mapSizeA *= 2 )
      for( size_t myOffA = 0; myOffA < 8; ++myOffA )
      {
         for( size_t mySizeA = dequeSize * ( mapSizeA - 1 ); mySizeA <= dequeSize * mapSizeA - myOffA % dequeSize; ++mySizeA )
         {
            deque< T > deque1;
            T ***map1 = reinterpret_cast< T *** > ( &deque1 );
            size_t *mapSize1 = reinterpret_cast< size_t * >( &deque1 ) + 1;
            size_t *myOff1 = reinterpret_cast< size_t * >( &deque1 ) + 2;
            size_t *mySize1 = reinterpret_cast< size_t * >( &deque1 ) + 3;

            *mapSize1 = mapSizeA;
            *map1 = new T * [ mapSizeA ]();
            *myOff1 = myOffA;
            *mySize1 = mySizeA;

            for( size_t block = myOffA / dequeSize; block <= ( myOffA + mySizeA - 1 ) / dequeSize; block++ )
               ( *map1 )[ block % mapSizeA ] = new T[ dequeSize ];

            for( size_t i = myOffA; i < myOffA + mySizeA; i++ )
            {
               size_t block = i % ( dequeSize * mapSizeA ) / dequeSize;
               ( *map1 )[ block ][ i % dequeSize ] = static_cast< T >( i );
            }

            for( size_t mapSizeB = 8; mapSizeB <= maxMapSize; mapSizeB *= 2 )
               for( size_t myOffB = dequeSize * ( mapSizeB - 1 ); myOffB < dequeSize * mapSizeB; ++myOffB )
               {
                  for( size_t mySizeB = dequeSize * ( mapSizeB - 1 ); mySizeB <= dequeSize * mapSizeB - myOffB % dequeSize; ++mySizeB )
                  {
                     deque< T > deque2;
                     T ***map2 = reinterpret_cast< T *** > ( &deque2 );
                     size_t *mapSize2 = reinterpret_cast< size_t * >( &deque2 ) + 1;
                     size_t *myOff2 = reinterpret_cast< size_t * >( &deque2 ) + 2;
                     size_t *mySize2 = reinterpret_cast< size_t * >( &deque2 ) + 3;

                     *mapSize2 = mapSizeB;
                     *map2 = new T * [ mapSizeB ]();
                     *myOff2 = myOffB;
                     *mySize2 = mySizeB;

                     for( size_t block = myOffB / dequeSize; block <= ( myOffB + mySizeB - 1 ) / dequeSize; block++ )
                        ( *map2 )[ block % mapSizeB ] = new T[ dequeSize ];

                     for( size_t i = myOffB; i < myOffB + mySizeB; i++ )
                     {
                        size_t block = i % ( dequeSize * mapSizeB ) / dequeSize;
                        ( *map2 )[ block ][ i % dequeSize ] = static_cast< T >( i );
                     }

                     deque2 = deque1;

                     T ***map3 = reinterpret_cast< T *** > ( &deque2 );
                     size_t *mapSize3 = reinterpret_cast< size_t * >( &deque2 ) + 1;
                     size_t *myOff3 = reinterpret_cast< size_t * >( &deque2 ) + 2;
                     size_t *mySize3 = reinterpret_cast< size_t * >( &deque2 ) + 3;

                     if( *myOff3 != myOffB ) // Note that mySizeA != 0
                        numErrors++;

                     if( *mySize3 != mySizeA )
                        numErrors++;

                     if( mySizeA <= mySizeB )
                     {
                        if( *mapSize3 != mapSizeB )
                           numErrors++;

                        if( *map3 != *map2 )
                           numErrors++;
                     }

                     for( size_t block = myOffB / dequeSize; block <= ( myOffB + mySizeB - 1 ) / dequeSize; block++ )
                        if( ( *map3 )[ block % mapSizeB ] != ( *map2 )[ block % mapSizeB ] )
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
            deque< T > deque1;
            T ***map1 = reinterpret_cast< T *** > ( &deque1 );
            size_t *mapSize1 = reinterpret_cast< size_t * >( &deque1 ) + 1;
            size_t *myOff1 = reinterpret_cast< size_t * >( &deque1 ) + 2;
            size_t *mySize1 = reinterpret_cast< size_t * >( &deque1 ) + 3;

            *mapSize1 = mapSizeA;
            *map1 = new T * [ mapSizeA ]();
            *myOff1 = myOffA;
            *mySize1 = mySizeA;

            for( size_t block = myOffA / dequeSize; block <= ( myOffA + mySizeA - 1 ) / dequeSize; block++ )
               ( *map1 )[ block % mapSizeA ] = new T[ dequeSize ];

            for( size_t i = myOffA; i < myOffA + mySizeA; i++ )
            {
               size_t block = i % ( dequeSize * mapSizeA ) / dequeSize;
               ( *map1 )[ block ][ i % dequeSize ] = static_cast< T >( i );
            }

            for( size_t mapSizeB = 8; mapSizeB <= maxMapSize; mapSizeB *= 2 )
               for( size_t myOffB = 0; myOffB < 8; ++myOffB )
               {
                  for( size_t mySizeB = 1; mySizeB <= 8; ++mySizeB )
                  {
                     deque< T > deque2;
                     T ***map2 = reinterpret_cast< T *** > ( &deque2 );
                     size_t *mapSize2 = reinterpret_cast< size_t * >( &deque2 ) + 1;
                     size_t *myOff2 = reinterpret_cast< size_t * >( &deque2 ) + 2;
                     size_t *mySize2 = reinterpret_cast< size_t * >( &deque2 ) + 3;

                     *mapSize2 = mapSizeB;
                     *map2 = new T * [ mapSizeB ]();
                     *myOff2 = myOffB;
                     *mySize2 = mySizeB;

                     for( size_t block = myOffB / dequeSize; block <= ( myOffB + mySizeB - 1 ) / dequeSize; block++ )
                        ( *map2 )[ block % mapSizeB ] = new T[ dequeSize ];

                     for( size_t i = myOffB; i < myOffB + mySizeB; i++ )
                     {
                        size_t block = i % ( dequeSize * mapSizeB ) / dequeSize;
                        ( *map2 )[ block ][ i % dequeSize ] = static_cast< T >( i );
                     }

                     deque2 = deque1;

                     T ***map3 = reinterpret_cast< T *** > ( &deque2 );
                     size_t *mapSize3 = reinterpret_cast< size_t * >( &deque2 ) + 1;
                     size_t *myOff3 = reinterpret_cast< size_t * >( &deque2 ) + 2;
                     size_t *mySize3 = reinterpret_cast< size_t * >( &deque2 ) + 3;

                     if( *myOff3 != myOffB ) // Note that mySizeA != 0
                        numErrors++;

                     if( *mySize3 != mySizeA )
                        numErrors++;

                     if( mySizeA <= mySizeB )
                     {
                        if( *mapSize3 != mapSizeB )
                           numErrors++;

                        if( *map3 != *map2 )
                           numErrors++;
                     }

                     for( size_t block = myOffB / dequeSize; block <= ( myOffB + mySizeB - 1 ) / dequeSize; block++ )
                        if( ( *map3 )[ block % mapSizeB ] != ( *map2 )[ block % mapSizeB ] )
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
            deque< T > deque1;
            T ***map1 = reinterpret_cast< T *** > ( &deque1 );
            size_t *mapSize1 = reinterpret_cast< size_t * >( &deque1 ) + 1;
            size_t *myOff1 = reinterpret_cast< size_t * >( &deque1 ) + 2;
            size_t *mySize1 = reinterpret_cast< size_t * >( &deque1 ) + 3;

            *mapSize1 = mapSizeA;
            *map1 = new T * [ mapSizeA ]();
            *myOff1 = myOffA;
            *mySize1 = mySizeA;

            for( size_t block = myOffA / dequeSize; block <= ( myOffA + mySizeA - 1 ) / dequeSize; block++ )
               ( *map1 )[ block % mapSizeA ] = new T[ dequeSize ];

            for( size_t i = myOffA; i < myOffA + mySizeA; i++ )
            {
               size_t block = i % ( dequeSize * mapSizeA ) / dequeSize;
               ( *map1 )[ block ][ i % dequeSize ] = static_cast< T >( i );
            }

            for( size_t mapSizeB = 8; mapSizeB <= maxMapSize; mapSizeB *= 2 )
               for( size_t myOffB = dequeSize * ( mapSizeB - 1 ); myOffB < dequeSize * mapSizeB; ++myOffB )
               {
                  for( size_t mySizeB = 1; mySizeB <= 8; ++mySizeB )
                  {
                     deque< T > deque2;
                     T ***map2 = reinterpret_cast< T *** > ( &deque2 );
                     size_t *mapSize2 = reinterpret_cast< size_t * >( &deque2 ) + 1;
                     size_t *myOff2 = reinterpret_cast< size_t * >( &deque2 ) + 2;
                     size_t *mySize2 = reinterpret_cast< size_t * >( &deque2 ) + 3;

                     *mapSize2 = mapSizeB;
                     *map2 = new T * [ mapSizeB ]();
                     *myOff2 = myOffB;
                     *mySize2 = mySizeB;

                     for( size_t block = myOffB / dequeSize; block <= ( myOffB + mySizeB - 1 ) / dequeSize; block++ )
                        ( *map2 )[ block % mapSizeB ] = new T[ dequeSize ];

                     for( size_t i = myOffB; i < myOffB + mySizeB; i++ )
                     {
                        size_t block = i % ( dequeSize * mapSizeB ) / dequeSize;
                        ( *map2 )[ block ][ i % dequeSize ] = static_cast< T >( i );
                     }

                     deque2 = deque1;

                     T ***map3 = reinterpret_cast< T *** > ( &deque2 );
                     size_t *mapSize3 = reinterpret_cast< size_t * >( &deque2 ) + 1;
                     size_t *myOff3 = reinterpret_cast< size_t * >( &deque2 ) + 2;
                     size_t *mySize3 = reinterpret_cast< size_t * >( &deque2 ) + 3;

                     if( *myOff3 != myOffB ) // Note that mySizeA != 0
                        numErrors++;

                     if( *mySize3 != mySizeA )
                        numErrors++;

                     if( mySizeA <= mySizeB )
                     {
                        if( *mapSize3 != mapSizeB )
                           numErrors++;

                        if( *map3 != *map2 )
                           numErrors++;
                     }

                     for( size_t block = myOffB / dequeSize; block <= ( myOffB + mySizeB - 1 ) / dequeSize; block++ )
                        if( ( *map3 )[ block % mapSizeB ] != ( *map2 )[ block % mapSizeB ] )
                           numErrors++;
                  }
               }
         }
      }
   }

   cout << "There are " << numErrors << " errors\n\n";
}

template< typename T >
void testAssignment25()
{
   size_t dequeSize = compDequeSize< T >(); // elements per block (a power of 2)

   const size_t maxMapSize = 32 * sizeof( T );
   size_t numErrors = 0;

   for( size_t mapSizeA = 8; mapSizeA <= maxMapSize; mapSizeA *= 2 )
   {
      for( size_t myOffA = dequeSize * ( mapSizeA - 1 ); myOffA < dequeSize * mapSizeA; ++myOffA )
      {
         for( size_t mySizeA = dequeSize * ( mapSizeA - 1 ); mySizeA <= dequeSize * mapSizeA - myOffA % dequeSize; ++mySizeA )
         {
            deque< T > deque1;
            T ***map1 = reinterpret_cast< T *** > ( &deque1 );
            size_t *mapSize1 = reinterpret_cast< size_t * >( &deque1 ) + 1;
            size_t *myOff1 = reinterpret_cast< size_t * >( &deque1 ) + 2;
            size_t *mySize1 = reinterpret_cast< size_t * >( &deque1 ) + 3;

            *mapSize1 = mapSizeA;
            *map1 = new T * [ mapSizeA ]();
            *myOff1 = myOffA;
            *mySize1 = mySizeA;

            for( size_t block = myOffA / dequeSize; block <= ( myOffA + mySizeA - 1 ) / dequeSize; block++ )
               ( *map1 )[ block % mapSizeA ] = new T[ dequeSize ];

            for( size_t i = myOffA; i < myOffA + mySizeA; i++ )
            {
               size_t block = i % ( dequeSize * mapSizeA ) / dequeSize;
               ( *map1 )[ block ][ i % dequeSize ] = static_cast< T >( i );
            }

            for( size_t mapSizeB = 8; mapSizeB <= maxMapSize; mapSizeB *= 2 )
               for( size_t myOffB = 0; myOffB < 8; ++myOffB )
               {
                  for( size_t mySizeB = 1; mySizeB <= 8; ++mySizeB )
                  {
                     deque< T > deque2;
                     T ***map2 = reinterpret_cast< T *** > ( &deque2 );
                     size_t *mapSize2 = reinterpret_cast< size_t * >( &deque2 ) + 1;
                     size_t *myOff2 = reinterpret_cast< size_t * >( &deque2 ) + 2;
                     size_t *mySize2 = reinterpret_cast< size_t * >( &deque2 ) + 3;

                     *mapSize2 = mapSizeB;
                     *map2 = new T * [ mapSizeB ]();
                     *myOff2 = myOffB;
                     *mySize2 = mySizeB;

                     for( size_t block = myOffB / dequeSize; block <= ( myOffB + mySizeB - 1 ) / dequeSize; block++ )
                        ( *map2 )[ block % mapSizeB ] = new T[ dequeSize ];

                     for( size_t i = myOffB; i < myOffB + mySizeB; i++ )
                     {
                        size_t block = i % ( dequeSize * mapSizeB ) / dequeSize;
                        ( *map2 )[ block ][ i % dequeSize ] = static_cast< T >( i );
                     }

                     deque2 = deque1;

                     T ***map3 = reinterpret_cast< T *** > ( &deque2 );
                     size_t *mapSize3 = reinterpret_cast< size_t * >( &deque2 ) + 1;
                     size_t *myOff3 = reinterpret_cast< size_t * >( &deque2 ) + 2;
                     size_t *mySize3 = reinterpret_cast< size_t * >( &deque2 ) + 3;

                     if( *myOff3 != myOffB ) // Note that mySizeA != 0
                        numErrors++;

                     if( *mySize3 != mySizeA )
                        numErrors++;

                     if( mySizeA <= mySizeB )
                     {
                        if( *mapSize3 != mapSizeB )
                           numErrors++;

                        if( *map3 != *map2 )
                           numErrors++;
                     }

                     for( size_t block = myOffB / dequeSize; block <= ( myOffB + mySizeB - 1 ) / dequeSize; block++ )
                        if( ( *map3 )[ block % mapSizeB ] != ( *map2 )[ block % mapSizeB ] )
                           numErrors++;
                  }
               }
         }

         if( ( sizeof( T ) == 1 && myOffA == dequeSize * mapSizeA - 1 ) ||
             ( sizeof( T ) > 1 && mapSizeA == maxMapSize && myOffA % 4 == 3 ) )
             cout << "There are " << numErrors << " errors\n";
      }
   }

   cout << endl;
}

template< typename T >
void testAssignment26()
{
   size_t dequeSize = compDequeSize< T >(); // elements per block (a power of 2)

   const size_t maxMapSize = 32 * sizeof( T );
   size_t numErrors = 0;

   for( size_t mapSizeA = 8; mapSizeA <= maxMapSize; mapSizeA *= 2 )
   {
      for( size_t myOffA = dequeSize * ( mapSizeA - 1 ); myOffA < dequeSize * mapSizeA; ++myOffA )
      {
         for( size_t mySizeA = dequeSize * ( mapSizeA - 1 ); mySizeA <= dequeSize * mapSizeA - myOffA % dequeSize; ++mySizeA )
         {
            deque< T > deque1;
            T ***map1 = reinterpret_cast< T *** > ( &deque1 );
            size_t *mapSize1 = reinterpret_cast< size_t * >( &deque1 ) + 1;
            size_t *myOff1 = reinterpret_cast< size_t * >( &deque1 ) + 2;
            size_t *mySize1 = reinterpret_cast< size_t * >( &deque1 ) + 3;

            *mapSize1 = mapSizeA;
            *map1 = new T * [ mapSizeA ]();
            *myOff1 = myOffA;
            *mySize1 = mySizeA;

            for( size_t block = myOffA / dequeSize; block <= ( myOffA + mySizeA - 1 ) / dequeSize; block++ )
               ( *map1 )[ block % mapSizeA ] = new T[ dequeSize ];

            for( size_t i = myOffA; i < myOffA + mySizeA; i++ )
            {
               size_t block = i % ( dequeSize * mapSizeA ) / dequeSize;
               ( *map1 )[ block ][ i % dequeSize ] = static_cast< T >( i );
            }

            for( size_t mapSizeB = 8; mapSizeB <= maxMapSize; mapSizeB *= 2 )
               for( size_t myOffB = 0; myOffB < 8; ++myOffB )
               {
                  for( size_t mySizeB = dequeSize * ( mapSizeB - 1 ); mySizeB <= dequeSize * mapSizeB - myOffB % dequeSize; ++mySizeB )
                  {
                     deque< T > deque2;
                     T ***map2 = reinterpret_cast< T *** > ( &deque2 );
                     size_t *mapSize2 = reinterpret_cast< size_t * >( &deque2 ) + 1;
                     size_t *myOff2 = reinterpret_cast< size_t * >( &deque2 ) + 2;
                     size_t *mySize2 = reinterpret_cast< size_t * >( &deque2 ) + 3;

                     *mapSize2 = mapSizeB;
                     *map2 = new T * [ mapSizeB ]();
                     *myOff2 = myOffB;
                     *mySize2 = mySizeB;

                     for( size_t block = myOffB / dequeSize; block <= ( myOffB + mySizeB - 1 ) / dequeSize; block++ )
                        ( *map2 )[ block % mapSizeB ] = new T[ dequeSize ];

                     for( size_t i = myOffB; i < myOffB + mySizeB; i++ )
                     {
                        size_t block = i % ( dequeSize * mapSizeB ) / dequeSize;
                        ( *map2 )[ block ][ i % dequeSize ] = static_cast< T >( i );
                     }

                     deque2 = deque1;

                     T ***map3 = reinterpret_cast< T *** > ( &deque2 );
                     size_t *mapSize3 = reinterpret_cast< size_t * >( &deque2 ) + 1;
                     size_t *myOff3 = reinterpret_cast< size_t * >( &deque2 ) + 2;
                     size_t *mySize3 = reinterpret_cast< size_t * >( &deque2 ) + 3;

                     if( *myOff3 != myOffB ) // Note that mySizeA != 0
                        numErrors++;

                     if( *mySize3 != mySizeA )
                        numErrors++;

                     if( mySizeA <= mySizeB )
                     {
                        if( *mapSize3 != mapSizeB )
                           numErrors++;

                        if( *map3 != *map2 )
                           numErrors++;
                     }

                     for( size_t block = myOffB / dequeSize; block <= ( myOffB + mySizeB - 1 ) / dequeSize; block++ )
                        if( ( *map3 )[ block % mapSizeB ] != ( *map2 )[ block % mapSizeB ] )
                           numErrors++;
                  }
               }
         }

         if( sizeof( T ) == 1 )
         {
            if( myOffA % 8 == 7 )
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

   const size_t maxMapSize = 32 * sizeof( T );
   size_t numErrors = 0;

   for( size_t mapSizeA = 8; mapSizeA <= maxMapSize; mapSizeA *= 2 )
      for( size_t myOffA = dequeSize * ( mapSizeA - 1 ); myOffA < dequeSize * mapSizeA; ++myOffA )
      {
         for( size_t mySizeA = dequeSize * ( mapSizeA - 1 ); mySizeA <= dequeSize * mapSizeA - myOffA % dequeSize; ++mySizeA )
         {
            deque< T > deque1;
            T ***map1 = reinterpret_cast< T *** > ( &deque1 );
            size_t *mapSize1 = reinterpret_cast< size_t * >( &deque1 ) + 1;
            size_t *myOff1 = reinterpret_cast< size_t * >( &deque1 ) + 2;
            size_t *mySize1 = reinterpret_cast< size_t * >( &deque1 ) + 3;

            *mapSize1 = mapSizeA;
            *map1 = new T * [ mapSizeA ]();
            *myOff1 = myOffA;
            *mySize1 = mySizeA;

            for( size_t block = myOffA / dequeSize; block <= ( myOffA + mySizeA - 1 ) / dequeSize; block++ )
               ( *map1 )[ block % mapSizeA ] = new T[ dequeSize ];

            for( size_t i = myOffA; i < myOffA + mySizeA; i++ )
            {
               size_t block = i % ( dequeSize * mapSizeA ) / dequeSize;
               ( *map1 )[ block ][ i % dequeSize ] = static_cast< T >( i );
            }

            for( size_t mapSizeB = 8; mapSizeB <= maxMapSize; mapSizeB *= 2 )
               for( size_t myOffB = dequeSize * ( mapSizeB - 1 ); myOffB < dequeSize * mapSizeB; ++myOffB )
               {
                  for( size_t mySizeB = 1; mySizeB <= 8; ++mySizeB )
                  {
                     deque< T > deque2;
                     T ***map2 = reinterpret_cast< T *** > ( &deque2 );
                     size_t *mapSize2 = reinterpret_cast< size_t * >( &deque2 ) + 1;
                     size_t *myOff2 = reinterpret_cast< size_t * >( &deque2 ) + 2;
                     size_t *mySize2 = reinterpret_cast< size_t * >( &deque2 ) + 3;

                     *mapSize2 = mapSizeB;
                     *map2 = new T * [ mapSizeB ]();
                     *myOff2 = myOffB;
                     *mySize2 = mySizeB;

                     for( size_t block = myOffB / dequeSize; block <= ( myOffB + mySizeB - 1 ) / dequeSize; block++ )
                        ( *map2 )[ block % mapSizeB ] = new T[ dequeSize ];

                     for( size_t i = myOffB; i < myOffB + mySizeB; i++ )
                     {
                        size_t block = i % ( dequeSize * mapSizeB ) / dequeSize;
                        ( *map2 )[ block ][ i % dequeSize ] = static_cast< T >( i );
                     }

                     deque2 = deque1;

                     T ***map3 = reinterpret_cast< T *** > ( &deque2 );
                     size_t *mapSize3 = reinterpret_cast< size_t * >( &deque2 ) + 1;
                     size_t *myOff3 = reinterpret_cast< size_t * >( &deque2 ) + 2;
                     size_t *mySize3 = reinterpret_cast< size_t * >( &deque2 ) + 3;

                     if( *myOff3 != myOffB ) // Note that mySizeA != 0
                        numErrors++;

                     if( *mySize3 != mySizeA )
                        numErrors++;

                     if( mySizeA <= mySizeB )
                     {
                        if( *mapSize3 != mapSizeB )
                           numErrors++;

                        if( *map3 != *map2 )
                           numErrors++;
                     }

                     for( size_t block = myOffB / dequeSize; block <= ( myOffB + mySizeB - 1 ) / dequeSize; block++ )
                        if( ( *map3 )[ block % mapSizeB ] != ( *map2 )[ block % mapSizeB ] )
                           numErrors++;
                  }
               }
         }

         if( sizeof( T ) == 1 )
         {
            if( myOffA % 8 == 7 )
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

   const size_t maxMapSize = 32 * sizeof( T );
   size_t numErrors = 0;

   for( size_t mapSizeA = 8; mapSizeA <= maxMapSize; mapSizeA *= 2 )
      for( size_t myOffA = dequeSize * ( mapSizeA - 1 ); myOffA < dequeSize * mapSizeA; ++myOffA )
      {
         for( size_t mySizeA = dequeSize * ( mapSizeA - 1 ); mySizeA <= dequeSize * mapSizeA - myOffA % dequeSize; ++mySizeA )
         {
            deque< T > deque1;
            T ***map1 = reinterpret_cast< T *** > ( &deque1 );
            size_t *mapSize1 = reinterpret_cast< size_t * >( &deque1 ) + 1;
            size_t *myOff1 = reinterpret_cast< size_t * >( &deque1 ) + 2;
            size_t *mySize1 = reinterpret_cast< size_t * >( &deque1 ) + 3;

            *mapSize1 = mapSizeA;
            *map1 = new T * [ mapSizeA ]();
            *myOff1 = myOffA;
            *mySize1 = mySizeA;

            for( size_t block = myOffA / dequeSize; block <= ( myOffA + mySizeA - 1 ) / dequeSize; block++ )
               ( *map1 )[ block % mapSizeA ] = new T[ dequeSize ];

            for( size_t i = myOffA; i < myOffA + mySizeA; i++ )
            {
               size_t block = i % ( dequeSize * mapSizeA ) / dequeSize;
               ( *map1 )[ block ][ i % dequeSize ] = static_cast< T >( i );
            }

            for( size_t mapSizeB = 8; mapSizeB <= maxMapSize; mapSizeB *= 2 )
               for( size_t myOffB = dequeSize * ( mapSizeB - 1 ); myOffB < dequeSize * mapSizeB; ++myOffB )
               {
                  for( size_t mySizeB = dequeSize * ( mapSizeB - 1 ); mySizeB <= dequeSize * mapSizeB - myOffB % dequeSize; ++mySizeB )
                  {
                     deque< T > deque2;
                     T ***map2 = reinterpret_cast< T *** > ( &deque2 );
                     size_t *mapSize2 = reinterpret_cast< size_t * >( &deque2 ) + 1;
                     size_t *myOff2 = reinterpret_cast< size_t * >( &deque2 ) + 2;
                     size_t *mySize2 = reinterpret_cast< size_t * >( &deque2 ) + 3;

                     *mapSize2 = mapSizeB;
                     *map2 = new T * [ mapSizeB ]();
                     *myOff2 = myOffB;
                     *mySize2 = mySizeB;

                     for( size_t block = myOffB / dequeSize; block <= ( myOffB + mySizeB - 1 ) / dequeSize; block++ )
                        ( *map2 )[ block % mapSizeB ] = new T[ dequeSize ];

                     for( size_t i = myOffB; i < myOffB + mySizeB; i++ )
                     {
                        size_t block = i % ( dequeSize * mapSizeB ) / dequeSize;
                        ( *map2 )[ block ][ i % dequeSize ] = static_cast< T >( i );
                     }

                     deque2 = deque1;

                     T ***map3 = reinterpret_cast< T *** > ( &deque2 );
                     size_t *mapSize3 = reinterpret_cast< size_t * >( &deque2 ) + 1;
                     size_t *myOff3 = reinterpret_cast< size_t * >( &deque2 ) + 2;
                     size_t *mySize3 = reinterpret_cast< size_t * >( &deque2 ) + 3;

                     if( *myOff3 != myOffB ) // Note that mySizeA != 0
                        numErrors++;

                     if( *mySize3 != mySizeA )
                        numErrors++;

                     if( mySizeA <= mySizeB )
                     {
                        if( *mapSize3 != mapSizeB )
                           numErrors++;

                        if( *map3 != *map2 )
                           numErrors++;
                     }

                     for( size_t block = myOffB / dequeSize; block <= ( myOffB + mySizeB - 1 ) / dequeSize; block++ )
                        if( ( *map3 )[ block % mapSizeB ] != ( *map2 )[ block % mapSizeB ] )
                           numErrors++;
                  }
               }
         }

         if( sizeof( T ) == 1 )
         {
            if( ( mapSizeA < maxMapSize && myOffA % 8 == 7 ) ||
                ( mapSizeA == maxMapSize && myOffA % 4 == 3 ) )
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