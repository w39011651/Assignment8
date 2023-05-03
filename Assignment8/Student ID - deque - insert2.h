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
      // elements per block (a power of 2)
      size_type dequeSize = sizeof( value_type ) <= 1 ? 16 :
                            sizeof( value_type ) <= 2 ?  8 :
                            sizeof( value_type ) <= 4 ?  4 :
                            sizeof( value_type ) <= 8 ?  2 : 1;

      size_type block = myCont->getBlock( myOff );
      size_type off = myOff % dequeSize;
      return &myCont->map[ block ][ off ];
   }
/*
   pointer operator->() const
   {
      return &( operator*() );
   }
*/
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

   // return length of sequence
   size_type size() const
   {
      return myData.mySize;
   }

   // test if sequence is empty
   bool empty() const
   {
      return myData.mySize == 0;
   }

   // insert val at where
   iterator insert( const_iterator where, const value_type &val )
   {
      size_type dequeSize = compDequeSize(); // elements per block (a power of 2)
      size_type off = static_cast< size_type >( where - begin() );
      if( myData.mySize == 0 )
      {
         if( myData.mapSize == 0 )
         {
            myData.map = new value_type * [ 8 ]();
            myData.mapSize = 8;
         }
         size_t row = (off / dequeSize) % myData.mapSize;
         size_t col = off % dequeSize;
         //find forward
         if (row == 0 && col == 0) {
             row = myData.mapSize - 1;
             col = dequeSize - 1;
         }
         else if (col == 0) {
             col = dequeSize - 1;
             row--;
         }
         else
             col -= 1;

         if (myData.map[row] == nullptr) {
             myData.map[row] = new value_type[dequeSize]();
         }
         myData.map[row][col] = val;
         myData.myOff = row * dequeSize + col;


      }
      else
      {
         // all elements before where move forward
         if( off <= myData.mySize / 2 )
         {
            if( myData.myOff % dequeSize == 0 &&
               myData.mapSize <= ( myData.mySize + dequeSize ) / dequeSize )
               doubleMapSize();
            if (myData.myOff >= myData.mapSize * dequeSize) {
                myData.myOff %= myData.mapSize * dequeSize;
            }

            //begin,row:i/dequeSize%mapSize, col=i%dequeSize
            size_t row = (myData.myOff / dequeSize) % myData.mapSize; //begin
            int targetRow = ((myData.myOff + off - 1) / dequeSize) % myData.mapSize;
            size_t col = myData.myOff % dequeSize;
            int targetCol = (myData.myOff + off - 1) % dequeSize;
            //check that is index out of range?
            if (targetRow < 0)
                targetRow += myData.mapSize;
            if (targetCol < 0)
                targetCol += dequeSize;
            //fix the negative index, following:find the forward index of begin
            if (row == 0 && col == 0) {
                if (myData.map[row + myData.mapSize - 1] == nullptr) {
                    myData.map[row + myData.mapSize - 1] = new value_type[dequeSize]();
                    row += myData.mapSize - 1;
                    col += dequeSize - 1;
                }
            }//map[0][0]
            else if (col == 0) {
                if (myData.map[row - 1] == nullptr) {
                    myData.map[row - 1] = new value_type[dequeSize]();
                    row--;
                    col += dequeSize - 1;
                }
            }//map[n][0]
            else {
                col--;
            }
            //following: move forward
            for (size_t i = 0; i < off; i++) {
                row = ((i + myData.myOff - 1) / dequeSize) % myData.mapSize;
                col = (i + myData.myOff - 1) % dequeSize;
                size_t nextRow, nextCol;

                if (row == myData.mapSize - 1 && col == dequeSize - 1) {
                    nextRow = 0;
                    nextCol = 0;
                }//change to first element;
                else if (col == dequeSize - 1) {
                    nextRow = row + 1;
                    nextCol = 0;
                }//change to next row
                else {
                    nextRow = row;
                    nextCol = col + 1;
                }//increase

                myData.map[row][col] = myData.map[nextRow][nextCol];
            }

            myData.map[targetRow][targetCol] = val;

            if (myData.myOff == 0)
                myData.myOff = myData.mapSize * dequeSize - 1;//是begin()-end()?
            else
                myData.myOff -= 1;


         }
         else  // all elements after (and at) where move backward
         {
            if( ( myData.myOff + myData.mySize ) % dequeSize == 0 &&
               myData.mapSize <= ( myData.mySize + dequeSize ) / dequeSize )
               doubleMapSize();
            if ((myData.myOff + myData.mySize) % dequeSize == 0 &&
                myData.mapSize <= (myData.mySize + dequeSize) / dequeSize)
                doubleMapSize();

            if (myData.myOff >= myData.mapSize * dequeSize) {
                myData.myOff %= myData.mapSize * dequeSize;
            }


            size_t row = ((myData.myOff + myData.mySize - 1) / dequeSize) % myData.mapSize;
            size_t col = (myData.myOff + myData.mySize - 1) % dequeSize;//find last index
            size_t nextRow = 0, nextCol = 0;
            size_t targetRow = ((myData.myOff + off) / dequeSize) % myData.mapSize;
            size_t targetCol = (myData.myOff + off) % dequeSize;
            if (row == myData.mapSize - 1 && col == dequeSize - 1) {
                nextRow = 0;
                nextCol = 0;
            }
            else if (col == dequeSize - 1) {
                nextRow = row + 1;
                nextCol = 0;
            }
            else {
                nextRow = row;
                nextCol = col + 1;//find the next of the last
            }
            if (myData.map[nextRow] == nullptr) {
                myData.map[nextRow] = new value_type[dequeSize]();
            }
            for (size_t i = 0; i < myData.mySize - off; i++) {
                row = ((myData.myOff + myData.mySize - i - 1) / dequeSize) % myData.mapSize;
                col = (myData.myOff + myData.mySize - i - 1) % dequeSize;
                myData.map[nextRow][nextCol] = myData.map[row][col];
                nextRow = row;
                nextCol = col;
            }
            myData.map[targetRow][targetCol] = val;


         }
      }

      ++myData.mySize;
      return begin() + static_cast< difference_type >( off );
   }

   // erase all
   void clear()
   {
      if( myData.mapSize > 0 )
      {
         for( size_type i = 0; i < myData.mapSize; i++ )
            if( myData.map[ i ] != nullptr )
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

   void doubleMapSize()
   {
      if( myData.mapSize > 0 )
      {
         size_type oldMapSize = myData.mapSize;
         myData.mapSize *= 2;
         value_type **newMap = new value_type * [ myData.mapSize ]();

         size_t dequeSize = compDequeSize();
         for (size_t i = myData.myOff; i < myData.mySize + myData.myOff; i++) {
             size_t createRow = (i / dequeSize) % myData.mapSize;
             newMap[createRow] = new value_type[dequeSize]();
         }
         //調整:myOff要一樣
         for (int i = myData.myOff; i < myData.myOff + myData.mySize; i++) {
             int leftrow = (i / dequeSize) % oldMapSize;
             int rightrow = (i / dequeSize) % myData.mapSize;
             int col = i % dequeSize;
             newMap[rightrow][col] = myData.map[leftrow][col];
         }

         delete[] myData.map;

         myData.map = newMap;
      }
   }

   size_type compDequeSize()
   {
      return sizeof( value_type ) <= 1 ? 16 : sizeof( value_type ) <= 2 ? 8 :
             sizeof( value_type ) <= 4 ?  4 : sizeof( value_type ) <= 8 ? 2 : 1;
   }

   ScaryVal myData;
};

#endif