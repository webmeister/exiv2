#include <stdint.h>

#include "slice.hpp"
#include "types.hpp"

#include <gtest/gtest.h>

using namespace Exiv2;

template <typename T>
class ASlice;

/*!
 * This namespace contains the helper-function getTestData. It is intented
 * to be used for tests with the slice fixture: it returns the appropriate
 * data to the constructor of slice. For (const) T==std::vector it returns the
 * fixtures member vec_, for (const) T==int* it returns vec_.data()
 *
 * As we don't have C++17 and can't use a single function with a big `constexpr
 * if`, we instead overload getTestData for the four types that we test.
 */
namespace cpp_pre_17_boilerplate
{
    int* getTestData(ASlice<int*>& st);

    const int* getTestData(ASlice<const int*>& st);

    std::vector<int>& getTestData(ASlice<std::vector<int> >& st);

    const std::vector<int>& getTestData(ASlice<const std::vector<int> >& st);
}  // namespace cpp_pre_17_boilerplate

/*!
 * Fixture for slice testing. Has one public vector of ints with size vec_size
 * that is filled with the numbers from 0 to vec_size - 1.
 *
 * The vector vec_ is used to construct slices either from a std::vector, or
 * from raw C-arrays. Which type is used, is set by the template parameter
 * T. Thus we guarantee, that the interface is completely independent of the
 * underlying datatype.
 *
 * @tparam T  Type that is used to construct a slice for testing.
 */
template <typename T>
class ASlice : public ::testing::Test
{
public:
    static const size_t vec_size = 10;

    Slice<T> getTestSlice(size_t begin = 1, size_t end = vec_size - 1)
    {
        return Slice<T>(cpp_pre_17_boilerplate::getTestData(*this), begin, end);
    }

    std::vector<int> vec_ = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
};

// implementation of the overloads of getTestData are provided here, since
// they must have the full definition of slice available
namespace cpp_pre_17_boilerplate
{
    int* getTestData(ASlice<int*>& st)
    {
        return st.vec_.data();
    }

    const int* getTestData(ASlice<const int*>& st)
    {
        return st.vec_.data();
    }

    std::vector<int>& getTestData(ASlice<std::vector<int> >& st)
    {
        return st.vec_;
    }

    const std::vector<int>& getTestData(ASlice<const std::vector<int> >& st)
    {
        return st.vec_;
    }
}  // namespace cpp_pre_17_boilerplate

/*!
 * Fixture to run test for mutable slices.
 *
 * It adds nothing new, it is just a separate class, so that we can run
 * different tests on it.
 */
template <typename T>
class mutableSlice : public ASlice<T>
{
};

/*!
 * Static assertions for ensuring that the types are sane
 */
static_assert(std::is_same<Slice<int*>::value_type, Slice<std::vector<int> >::value_type>::value,
              "value types of Slice<int*> and Slice<std::vector<int>> differ");
static_assert(std::is_same<Slice<int*>::iterator, int*>::value, "Slice<int*>::iterator is not int*");
static_assert(std::is_same<Slice<int*>::const_iterator, int const*>::value, "Slice<int*>::iterator is not int*");

static_assert(std::is_same<Slice<const int*>::value_type, Slice<const std::vector<int> >::value_type>::value,
              "value types of Slice<const int*> and Slice<const std::vector<int>> differ");
static_assert(std::is_same<Slice<const int*>::iterator, int const*>::value,
              "Slice<const int*>::iterator is not int const*");
static_assert(std::is_same<Slice<const int*>::const_iterator, int const*>::value,
              "Slice<const int*>::iterator is not int const*");

TYPED_TEST_CASE_P(ASlice);
TYPED_TEST_CASE_P(mutableSlice);

TYPED_TEST_P(ASlice, atAccess)
{
    Slice<TypeParam> slice = this->getTestSlice();

    ASSERT_EQ(this->vec_.size() - 2, slice.size());

    for (unsigned int i = 0; i < slice.size(); ++i) {
        ASSERT_EQ(this->vec_.at(i + 1), slice.at(i));
    }
}

TYPED_TEST_P(ASlice, atOutOfBoundsAccess)
{
    Slice<TypeParam> slice = this->getTestSlice();

    ASSERT_THROW(slice.at(slice.size()), std::out_of_range);
    ASSERT_THROW(slice.at(slice.size() + 1), std::out_of_range);
}

TYPED_TEST_P(ASlice, iteratorAccess)
{
    Slice<TypeParam> slice = this->getTestSlice();

    auto vec_it = this->vec_.begin() + 1;
    for (typename Slice<TypeParam>::const_iterator it = slice.cbegin(); it < slice.cend(); ++it, ++vec_it) {
        ASSERT_EQ(*it, *vec_it);
    }
}

TYPED_TEST_P(ASlice, rangeBasedForLoop)
{
    auto slice = this->getTestSlice();
    auto vec_iter = this->vec_.begin() + 1;
    for (const auto& val : slice) {
        ASSERT_EQ(val, *vec_iter);
        ++vec_iter;
    }
}

TYPED_TEST_P(ASlice, constructionFailsFromInvalidRange)
{
    // start > end
    ASSERT_THROW(this->getTestSlice(2, 1), std::out_of_range);
}

TYPED_TEST_P(ASlice, constructionFailsWithZeroLength)
{
    ASSERT_THROW(this->getTestSlice(1, 1), std::out_of_range);
}

/*!
 * Test the construction of subSlices and their behavior.
 */
TYPED_TEST_P(ASlice, subSliceSuccessfulConstruction)
{
    typedef Slice<TypeParam> slice_t;

    // 0 1 2 3 4 5 6 7 8 9
    //       |     |       center_vals
    //         | |         middle
    slice_t center_vals = this->getTestSlice(3, 7);
    ASSERT_EQ(center_vals.size(), static_cast<size_t>(4));
    ASSERT_NO_THROW(center_vals.subSlice(1, 3));

    ASSERT_NO_THROW(center_vals.subSlice(1, center_vals.size()));
}

TYPED_TEST_P(ASlice, subSliceFunctions)
{
    Slice<TypeParam> middle = this->getTestSlice(3, 7).subSlice(1, 3);

    ASSERT_EQ(middle.size(), static_cast<size_t>(2));
    ASSERT_EQ(middle.at(1), static_cast<typename Slice<TypeParam>::value_type>(5));
}

TYPED_TEST_P(ASlice, subSliceFailedConstruction)
{
    // 0 1 2 3 4 5 6 7 8 9
    //       |     |       middle
    Slice<TypeParam> middle = this->getTestSlice(3, 7);

    ASSERT_EQ(middle.size(), 4);

    // these are all invalid
    ASSERT_THROW(middle.subSlice(1, 6), std::out_of_range);
    ASSERT_THROW(middle.subSlice(1, 5), std::out_of_range);
    ASSERT_THROW(middle.subSlice(5, 1), std::out_of_range);

    // rejected by Slice constructor
    ASSERT_THROW(middle.subSlice(2, 2), std::out_of_range);
}

/*! try to cause integer overflows in a sub-optimal implementation */
TYPED_TEST_P(ASlice, subSliceConstructionOverflowResistance)
{
    Slice<TypeParam> center_vals = this->getTestSlice(3, 7);

    ASSERT_THROW(center_vals.subSlice(std::numeric_limits<size_t>::max() - 2, 3), std::out_of_range);
    ASSERT_THROW(center_vals.subSlice(2, std::numeric_limits<size_t>::max() - 1), std::out_of_range);
}

/*!
 * This function's purpose is only to check whether we can pass all slices by
 * constant reference.
 */
template <typename T>
void checkConstSliceValueAt(const Slice<T>& slice, typename Slice<T>::value_type value, size_t index)
{
    ASSERT_EQ(slice.at(index), value);
}

/*!
 * Check that the contents of the slice are ascending via an iterator based for
 * loop.
 */
template <typename T>
void checkConstSliceIterator(const Slice<T>& slice, typename Slice<T>::value_type first_value)
{
    auto first_value_copy = first_value;

    for (typename Slice<T>::const_iterator it = slice.cbegin(); it < slice.cend(); ++it) {
        ASSERT_EQ(*it, first_value++);
    }

    for (const auto& it : slice) {
        ASSERT_EQ(it, first_value_copy++);
    }
}

template <typename T>
void checkSubSlice(const Slice<T>& slice)
{
    ASSERT_EQ(slice.at(1), slice.subSlice(1, slice.size()).at(0));
}

/*!
 * Test that all slices can be also passed as const references and still work
 */
TYPED_TEST_P(ASlice, constMethodsPreserveConst)
{
    typedef Slice<TypeParam> slice_t;

    // 0 1 2 3 4 5 6 7 8 9
    //       |     |       center_vals
    slice_t center_vals = this->getTestSlice(3, 7);

    // check at() const works
    checkConstSliceValueAt(center_vals, 4, 1);

    checkConstSliceIterator(center_vals, 3);

    checkSubSlice(center_vals);
}

/*!
 * Test the non-const iterators
 */
TYPED_TEST_P(mutableSlice, iterators)
{
    typedef Slice<TypeParam> slice_t;
    slice_t slice = this->getTestSlice();

    ASSERT_EQ(*slice.begin(), static_cast<typename slice_t::value_type>(1));
    ASSERT_EQ(*slice.end(), static_cast<typename slice_t::value_type>(this->vec_size - 1));

    for (typename slice_t::iterator it = slice.begin(); it < slice.end(); ++it) {
        *it = 2 * (*it);
    }

    ASSERT_EQ(this->vec_.at(0), 0);
    for (size_t j = 1; j < this->vec_size - 1; ++j) {
        ASSERT_EQ(this->vec_.at(j), static_cast<typename slice_t::value_type>(2 * j));
        ASSERT_EQ(this->vec_.at(j), slice.at(j - 1));
    }
    ASSERT_EQ(this->vec_.at(this->vec_size - 1), static_cast<typename slice_t::value_type>(this->vec_size - 1));
}

/*!
 * Test the C++11 range based for loop
 */
TYPED_TEST_P(mutableSlice, rangeBasedForLoop)
{
    Slice<TypeParam> slice = this->getTestSlice();

    // revert the changes again
    for (auto& val : slice) {
        val *= 2;
    }
    size_t i = 1;
    for (const auto& val : slice) {
        ASSERT_EQ(val, 2 * i);
        ++i;
    }
}

/*!
 * Test the non-const version of at()
 */
TYPED_TEST_P(mutableSlice, at)
{
    typedef Slice<TypeParam> slice_t;
    slice_t slice = this->getTestSlice(2, 4);

    slice.at(0) = 6;
    slice.at(1) = 12;

    ASSERT_EQ(this->vec_.at(2), 6);
    ASSERT_EQ(this->vec_.at(3), 12);
    for (size_t j = 0; j < this->vec_size - 1; ++j) {
        if (j == 2 || j == 3) {
            continue;
        }
        ASSERT_EQ(this->vec_.at(j), static_cast<typename slice_t::value_type>(j));
    }
}

TEST(pointerSlice, failedConstructionFromNullpointer)
{
    ASSERT_THROW(Slice<long*>(nullptr, 1, 2), std::invalid_argument);
}

/*!
 * Test the construction of an invalid slices from a container (so that a proper
 * range check can be conducted)
 */
TEST(containerSlice, failedConstructionFromContainer)
{
    std::vector<int> tmp(10);
    // slice end too large
    ASSERT_THROW(Slice<std::vector<int> >(tmp, 1, tmp.size() + 1), std::out_of_range);
}

/*!
 * Test all functions from the makeSlice* family.
 */
TEST(containerSlice, makeSlice)
{
    std::string str = "this is a sentence";

    Slice<std::string> is = makeSlice(str, 5, 7);
    ASSERT_TRUE(std::equal(is.begin(), is.end(), "is"));

    Slice<std::string> sl_this = makeSliceUntil(str, 4);
    ASSERT_TRUE(std::equal(sl_this.begin(), sl_this.end(), "this"));

    Slice<std::string> sl_sentence = makeSliceFrom(str, 10);
    ASSERT_TRUE(std::equal(sl_sentence.begin(), sl_sentence.end(), "sentence"));

    Slice<std::string> sl_full = makeSlice(str);
    ASSERT_TRUE(std::equal(sl_full.begin(), sl_full.end(), str.c_str()));
}

struct stringSlice : public ::testing::Test
{
    std::string sentence;

    virtual void SetUp()
    {
        sentence = "this is a sentence";
    }
};

TEST_F(stringSlice, at)
{
    const Slice<const std::string> is_a = makeSlice(static_cast<const std::string&>(this->sentence), 5, 10);

    ASSERT_EQ(is_a.at(0), 'i');
    ASSERT_EQ(is_a.at(4), ' ');
}

TEST_F(stringSlice, atFailure)
{
    const Slice<const std::string> is_a = makeSlice(static_cast<const std::string&>(this->sentence), 5, 10);
    ASSERT_THROW(is_a.at(5), std::out_of_range);
}

TEST_F(stringSlice, size)
{
    const Slice<const std::string> is_a = makeSlice(static_cast<const std::string&>(this->sentence), 5, 10);
    ASSERT_EQ(is_a.size(), static_cast<size_t>(5));
}

TEST_F(stringSlice, mutateString)
{
    Slice<std::string> is_a_mutable = makeSlice(this->sentence, 5, 10);

    for (Slice<std::string>::iterator it = is_a_mutable.begin(); it < is_a_mutable.end(); ++it) {
        *it = ' ';
    }

    ASSERT_STREQ(this->sentence.c_str(), "this      sentence");
}

template <typename T>
struct dataBufSlice : public ::testing::Test
{
    static byte data[4];  // = {0xde, 0xad, 0xbe, 0xef};
    DataBuf buf;

    virtual void SetUp()
    {
        buf = DataBuf(data, sizeof(data));
    }
};

template <typename T>
byte dataBufSlice<T>::data[4] = {0xde, 0xad, 0xbe, 0xef};

TYPED_TEST_CASE_P(dataBufSlice);

TYPED_TEST_P(dataBufSlice, successfulConstruction)
{
    // just check that makeSlice appears to work
    ASSERT_EQ(makeSlice(static_cast<TypeParam>(this->buf), 1, 3).size(), static_cast<size_t>(2));
}

TYPED_TEST_P(dataBufSlice, failedConstruction)
{
    // check that we get an exception when end is larger than LONG_MAX
    ASSERT_THROW(
        makeSlice(static_cast<TypeParam>(this->buf), 1, static_cast<size_t>(std::numeric_limits<long>::max()) + 1),
        std::invalid_argument);

    // check that we get an exception when end is larger than the DataBuf
    ASSERT_THROW(makeSlice(static_cast<TypeParam>(this->buf), 1, 5), std::out_of_range);
}

//
// GTest boilerplate to get the tests running for all the different types
//
REGISTER_TYPED_TEST_CASE_P(ASlice, atAccess, atOutOfBoundsAccess, iteratorAccess, rangeBasedForLoop,
                           constructionFailsFromInvalidRange, constructionFailsWithZeroLength,
                           subSliceSuccessfulConstruction, subSliceFunctions, subSliceFailedConstruction,
                           subSliceConstructionOverflowResistance, constMethodsPreserveConst);

typedef ::testing::Types<const std::vector<int>, std::vector<int>, int*, const int*> test_types_t;
INSTANTIATE_TYPED_TEST_CASE_P(, ASlice, test_types_t);

REGISTER_TYPED_TEST_CASE_P(mutableSlice, iterators, rangeBasedForLoop, at);
typedef ::testing::Types<std::vector<int>, int*> mut_test_types_t;
INSTANTIATE_TYPED_TEST_CASE_P(, mutableSlice, mut_test_types_t);

REGISTER_TYPED_TEST_CASE_P(dataBufSlice, successfulConstruction, failedConstruction);
typedef ::testing::Types<DataBuf&, const DataBuf&> data_buf_types_t;
INSTANTIATE_TYPED_TEST_CASE_P(, dataBufSlice, data_buf_types_t);
