#ifndef DEQUE_H
#define DEQUE_H

// CLASS TEMPLATE DequeConstIterator
template< typename MyDeque >
class DequeConstIterator // iterator for nonmutable deque
{
private:
   using size_type = typename MyDeque::size_type;

public:
   using value_type = typename MyDeque::value_type;
   using difference_type = typename MyDeque::difference_type;
   using pointer = typename MyDeque::const_pointer;
   using reference = const value_type &;

   // construct with null pointer
   DequeConstIterator()
      : myOff( 0 ),
      myCont( nullptr )
   {
   }

   // construct with offset off in *pDeque
   DequeConstIterator( size_type off, const MyDeque *pDeque )
      : myOff( off ),
      myCont( pDeque )
   {
   }

   DequeConstIterator( const DequeConstIterator &right ) // copy constructor
      : myOff( right.myOff ),
      myCont( right.myCont )
   {
   }

   ~DequeConstIterator() // destructor
   {
   }

   // const return avoids: ( a1 = a2 ) = a3
   const DequeConstIterator& operator=( const DequeConstIterator &right )
   {
      if( &right != this ) // avoid self-assignment
      {
         myCont = right.myCont;
         myOff = right.myOff;
      }
      return *this; // enables x = y = z, for example
   }

   reference operator*() const
   {
      // elements per block (a power of 2)
      size_type dequeSize = sizeof( value_type ) <= 1 ? 16 :
                            sizeof( value_type ) <= 2 ?  8 :
                            sizeof( value_type ) <= 4 ?  4 :
                            sizeof( value_type ) <= 8 ?  2 : 1;

//      size_type block = myOff % ( dequeSize * myCont->mapSize ) / dequeSize;
      size_type block = myCont->getBlock( myOff );
      size_type off = myOff % dequeSize;
      return myCont->map[ block ][ off ];
   }

   pointer operator->() const
   {
      return &( operator*() );
   }

   DequeConstIterator& operator++() // preincrement
   {
      ++myOff;
      return *this;
   }

   DequeConstIterator operator++( int ) // postincrement
   {
      DequeConstIterator tmp = *this;
      ++*this;
      return tmp;
   }

   DequeConstIterator& operator--() // predecrement
   {
      --myOff;
      return *this;
   }

   DequeConstIterator operator--( int ) // postdecrement
   {
      DequeConstIterator tmp = *this;
      --*this;
      return tmp;
   }

   // increment by integer
   DequeConstIterator& operator+=( const difference_type off )
   {
      myOff += off;
      return *this;
   }

   // return this + integer
   DequeConstIterator operator+( const difference_type off ) const
   {
      DequeConstIterator tmp = *this;
      return tmp += off;
   }

   // decrement by integer
   DequeConstIterator& operator-=( const difference_type off )
   {
      return *this += -off;
   }

   // return this - integer
   DequeConstIterator operator-( const difference_type off ) const
   {
      DequeConstIterator tmp = *this;
      return tmp -= off;
   }

   // return difference of iterators
   difference_type operator-( const DequeConstIterator &right ) const
   {
      return ( static_cast< difference_type >( this->myOff - right.myOff ) );
   }

   reference operator[]( const difference_type off ) const // subscript
   {
      return *( *this + off );
   }

   // test for iterator equality
   bool operator==( const DequeConstIterator &right ) const
   {
      return this->myCont == right.myCont && this->myOff == right.myOff;
   }

   // test for iterator inequality
   bool operator!=( const DequeConstIterator &right ) const
   {
      return !( *this == right );
   }

   // test if this < right
   bool operator<( const DequeConstIterator &right ) const
   {
      return this->myOff < right.myOff;
   }

   // test if this > right
   bool operator>( const DequeConstIterator &right ) const
   {
      return right < *this;
   }

   // test if this <= right
   bool operator<=( const DequeConstIterator &right ) const
   {
      return !( right < *this );
   }

   // test if this >= right
   bool operator>=( const DequeConstIterator &right ) const
   {
      return !( *this < right );
   }

   const MyDeque *myCont; // keep a pointer to deque
   size_type myOff;       // offset of element in deque
};


// CLASS TEMPLATE DequeIterator
template< typename MyDeque >
class DequeIterator : public DequeConstIterator< MyDeque >
{ // iterator for mutable deque
private:
   using size_type = typename MyDeque::size_type;
   using MyBase = DequeConstIterator< MyDeque >;

public:
   using value_type = typename MyDeque::value_type;
   using difference_type = typename MyDeque::difference_type;
   using pointer = typename MyDeque::pointer;
   using reference = value_type &;

   using MyBase::MyBase;

   DequeIterator() // construct with null deque pointer
   {
   }

   DequeIterator( size_type off, const MyDeque *pDeque )
      : MyBase( off, pDeque ) // construct with offset off in *pDeque
   {
   }

   reference operator*() const // return designated object
   {
      return const_cast< reference >( MyBase::operator*() );
   }

   pointer operator->() const // return pointer to class object
   {
      return const_cast< pointer >( MyBase::operator->() );
      //      return &( operator*() );
   }

   DequeIterator& operator++() // preincrement
   {
      MyBase::operator++();
      return *this;
   }

   DequeIterator operator++( int ) // postincrement
   {
      DequeIterator tmp = *this;
      MyBase::operator++();
      return tmp;
   }

   DequeIterator& operator--() // predecrement
   {
      MyBase::operator--();
      return *this;
   }

   DequeIterator operator--( int ) // postdecrement
   {
      DequeIterator tmp = *this;
      MyBase::operator--();
      return tmp;
   }

   // increment by integer
   DequeIterator& operator+=( const difference_type off )
   {
      MyBase::operator+=( off );
      return *this;
   }

   // return this + integer
   DequeIterator operator+( const difference_type off ) const
   {
      DequeIterator tmp = *this;
      return tmp += off;
   }

   // decrement by integer
   DequeIterator& operator-=( const difference_type off )
   {
      MyBase::operator-=( off );
      return *this;
   }

   using MyBase::operator-; // return difference of iterators

   // return this - integer
   DequeIterator operator-( const difference_type off ) const
   {
      DequeIterator tmp = *this;
      return tmp -= off;
   }

   reference operator[]( const difference_type off ) const // subscript
   {
      return const_cast< reference >( MyBase::operator[]( off ) );
   }
};

// CLASS TEMPLATE DequeVal
template< typename Ty >
class DequeVal // base class for deque to hold data
{
public:
   using value_type = Ty;
   using size_type = size_t;
   using difference_type = ptrdiff_t;
   using pointer = value_type *;
   using const_pointer = const value_type *;
   using reference = value_type &;
   using const_reference = const value_type &;
   using MapPtr = Ty **;

   DequeVal() // initialize values
      : map(),
      mapSize( 0 ),
      myOff( 0 ),
      mySize( 0 )
   {
   }

   // determine block from offset
   size_type getBlock( size_type off ) const
   {
      // elements per block (a power of 2)
      size_type dequeSize = sizeof( value_type ) <= 1 ? 16 :
                            sizeof( value_type ) <= 2 ?  8 :
                            sizeof( value_type ) <= 4 ?  4 :
                            sizeof( value_type ) <= 8 ?  2 : 1;

      return off % ( dequeSize * mapSize ) / dequeSize;
//      return ( off / dequeSize ) & ( mapSize - 1 );
   }

   MapPtr map;        // pointer to array of pointers to blocks
   size_type mapSize; // size of map array, zero or 2^N
   size_type myOff;   // offset of initial element
   size_type mySize;  // current length of sequence
};


// CLASS TEMPLATE deque
template< typename Ty >
class deque // circular queue of pointers to blocks
{
private:
   using MapPtr = Ty **;
   using ScaryVal = DequeVal< Ty >;

public:
   using value_type = Ty;
   using size_type = size_t;
   using difference_type = ptrdiff_t;
   using pointer = value_type *;
   using const_pointer = const value_type *;
   using reference = value_type &;
   using const_reference = const value_type &;

   using iterator = DequeIterator< ScaryVal >;
   using const_iterator = DequeConstIterator< ScaryVal >;

   // construct empty deque
   deque()
      : myData()
   {
   }

   // construct by copying right
   deque( const deque &right )
      : myData()
   {
      if( right.myData.mySize > 0 )
      {
         size_type dequeSize = compDequeSize();

         myData.mySize = right.myData.mySize;
         myData.mapSize = 8;
         while( myData.mySize > dequeSize * ( myData.mapSize - 1 ) )
            myData.mapSize *= 2;
         size_type elementCounter = 0;
         //create 1-dimension dynamic array
         myData.map = new pointer[myData.mapSize]();
         //create 2-dimension dynamic array
         for (size_t i = 0; i < myData.mapSize; i++) {
             myData.map[i] = new value_type[dequeSize]();
             elementCounter += dequeSize;
             if (elementCounter >= right.myData.mySize) {
                 break;
             }
         }
         elementCounter = 0;//initial
         //copy the elements from right-hand-side object
         size_t rightStart = right.myData.myOff / dequeSize, //example 56/4=14,57/4=14
             rightSubStart = right.myData.myOff % dequeSize,//56%4=0, 57%4=1
             leftIndex = 0, rightIndex = 0;
         for (size_t i = 0; elementCounter!=myData.mySize; i++) {
             for (size_t j = 0; j < dequeSize; j++) {
                 rightIndex = (j + rightSubStart);
                 if (rightIndex >= dequeSize) {
                     leftIndex = (i + rightStart + 1) % right.myData.mapSize;
                     rightIndex -=dequeSize;
                 }
                 else {
                     leftIndex = (i + rightStart) % right.myData.mapSize;
                 }
                 myData.map[i][j] = right.myData.map[leftIndex][rightIndex];
                 //before line problem : if j+rightSubStart>=4, then start need plus 1
                 elementCounter++;
                 if (elementCounter == myData.mySize) {
                     break;
                 }
             }
         }

      }
   }

   // destroy the deque
   ~deque()
   {
      clear();
   }

   // return iterator for beginning of mutable sequence
   iterator begin()
   {
      return iterator( myData.myOff, &myData );
   }

   // return iterator for beginning of nonmutable sequence
   const_iterator begin() const
   {
      return const_iterator( myData.myOff, &myData );
   }

   // return iterator for end of mutable sequence
   iterator end()
   {
      return iterator( myData.myOff + myData.mySize, &myData );
   }

   // return iterator for end of nonmutable sequence
   const_iterator end() const
   {
      return const_iterator( myData.myOff + myData.mySize, &myData );
   }

   iterator makeIter( const_iterator where ) const
   {
      return iterator( where.myOff, &myData );
   }

   // erase all
   void clear()
   {
      if( myData.mapSize > 0 )
      {
         for( size_type i = 0; i < myData.mapSize; i++ )
            delete[] myData.map[ i ];
         delete[] myData.map;

         myData.mapSize = 0;
         myData.mySize = 0;
         myData.myOff = 0;
         myData.map = nullptr;
      }
   }

private:

   // determine block from offset
   size_type getBlock( size_type off ) const
   {
      return myData.getBlock( off );
//      return ( ( myData.off / compDequeSize() ) & ( myData.mapSize - 1 ) );
   }

   size_type compDequeSize()
   {
      return sizeof( value_type ) <= 1 ? 16 : sizeof( value_type ) <= 2 ? 8 :
             sizeof( value_type ) <= 4 ?  4 : sizeof( value_type ) <= 8 ? 2 : 1;
   }

   ScaryVal myData;
};

#endif