/*
 * bsk_test.cpp
 *
 *  Created on: Oct 18, 2016
 *      Author: timppa
 */

#include "gtest_inc.h"

#include "chip.h"

#include "bsk.h"

namespace BSK4_test_namespace {
	//
	// dependency injections
	//
int disp_show_decimal( int );
int i2c_read(int address,
		char* reg,int reglen,
		char* buffer,int length);
	//
	// delay dependency
	//
	int bsk_get_throw(bsk_frame_t* pFrame,int index);
	int bsk_calculate(bsk_game_t* pGame,int frames);
	int bsk_valid_frame(bsk_frame_t* pFrame);
	int my_bsk_get_throw(unsigned char* frame, int index);
	//
	// target code is included instead of (direct) compilation:
	//   This allows to cut the dependencies (such as I2C_write above)
	//
	#include "../src/bsk4.cpp"
}

using ::testing::Test;

/**********************************************************************
 *
 * GoogleTest test-class for 7-segment display testing
 *
 **********************************************************************/
class unittest_BSK4 : public Test
{
public:
	//
	// constructor just resets attributes to some default values
	//
	unittest_BSK4()
	{
		mRc = -1;
	}
	virtual ~unittest_BSK4(){}
protected:
	//
	// SetUp performs the per-test initialization/setup of test instance
	//
	virtual void SetUp()
	{
		mRc = -1;
		unittest_BSK4::mRecorded_valid_frame_result = 0;
	}
	//
	// TearDown cleans-up test instance
	//
	virtual void TearDown()
	{
	}
	static int getRecorded_Disp_Show_Decimal_Value()
	{
		return mRecorded_Disp_Show_Decimal_Value;
	}
	static void set_next_i2c_read_value( int i2c_rd )
	{
		mPlay_i2c_read_value = i2c_rd;
	}
	static void set_valid_frame_result(int r)
	{
		unittest_BSK4::mRecorded_valid_frame_result = r;
	}
	static void set_calculate_result(int r)
	{
		unittest_BSK4::mRecorded_calculate_result = r;
	}
protected:
	int mRc;
	// allow disp_show_decimal to modify attributes such as mRecorded_Disp_Show_Value
	friend int BSK4_test_namespace::disp_show_decimal( int value );
	static int mRecorded_Disp_Show_Decimal_Value;

	friend int BSK4_test_namespace::i2c_read(int address,
			char* reg,int reglen,
			char* buffer,int length);
	static int mPlay_i2c_read_value;
	static int mRecorded_i2c_read_address;
	//
	friend int BSK4_test_namespace::bsk_get_throw(bsk_frame_t* pFrame,int index);
	friend int BSK4_test_namespace::bsk_calculate(bsk_game_t* pGame,int frames);
	friend int BSK4_test_namespace::bsk_valid_frame(bsk_frame_t* pFrame);
	static int mRecorded_valid_frame_result;
	static int mRecorded_calculate_result;
};

//
// for use by disp_show_decimal
//
int unittest_BSK4::mRecorded_Disp_Show_Decimal_Value = 0;
//
// for use by i2c_read
//
int unittest_BSK4::mPlay_i2c_read_value = 0;
int unittest_BSK4::mRecorded_i2c_read_address = 0;

int BSK4_test_namespace::disp_show_decimal( int value )
{
	unittest_BSK4::mRecorded_Disp_Show_Decimal_Value = value;
}

int BSK4_test_namespace::i2c_read(int address,
		char* reg,int reglen,
		char* buffer,int length)
{
	static int data_index = 0;

	// no negative nums here!
	unsigned char dummydata[] = {
			1,2,3,4,5,6
	};

	if (address != HW_BSK_PIN_COUNTER)
		goto err;

	if (0 != reg || 0 != reglen)
		goto err;

	for (int i = 0; i < length; i++) {
		buffer[i] = dummydata[data_index];
		data_index++;
	}

	return 1;

	/*unittest_BSK4::mRecorded_i2c_read_address = address;
	if ( 0!=buffer && length>0 ){
		buffer[0]=unittest_BSK4::mPlay_i2c_read_value;
		return 1;
	}*/

err:
	return -1;
}

//
// mock bsk_get_throw
//
int BSK4_test_namespace::bsk_get_throw(bsk_frame_t* pFrame,int index)
{
	return 0;
}

int BSK4_test_namespace::my_bsk_get_throw(unsigned char* frame, int index) {

}

//
// mock bsk_calculate
//
int unittest_BSK4::mRecorded_calculate_result = 0;
int BSK4_test_namespace::bsk_calculate(bsk_game_t* pGame,int frames)
{
	return unittest_BSK4::mRecorded_calculate_result;
}

//
// mock bsk_valid_frame
//
int unittest_BSK4::mRecorded_valid_frame_result = 0;
int BSK4_test_namespace::bsk_valid_frame(bsk_frame_t* pFrame)
{
	return unittest_BSK4::mRecorded_valid_frame_result;
}

/**********************************************************************
 *
 * quick verification of test fixture
 * - this helps detect problems in test setup
 *
 **********************************************************************/
TEST_F( unittest_BSK4, test_fixture )
{
	EXPECT_EQ( -1, mRc );
}

/**********************************************************************
 *
 * quick verification of test setup/construction
 * - this helps detect problems in test setup
 *
 **********************************************************************/

TEST_F( unittest_BSK4, test_constructor )
{
}

/**********************************************************************
 *
 * test cases
 *
 **********************************************************************/

//
// test matches the empty implementation
//
TEST_F( unittest_BSK4, play_game )
{
	mRc = BSK4_test_namespace::play_game();
	EXPECT_EQ( -1, mRc );

	EXPECT_EQ( 0, getRecorded_Disp_Show_Decimal_Value() );

}

TEST_F( unittest_BSK4, i2c_testdata_read )
{
	char data = 0;

	EXPECT_EQ(1, BSK4_test_namespace::i2c_read(HW_BSK_PIN_COUNTER, 0,0, &data, 1));
	EXPECT_EQ(1, data);
	EXPECT_EQ(1, BSK4_test_namespace::i2c_read(HW_BSK_PIN_COUNTER, 0,0, &data, 1));
	EXPECT_EQ(2, data);
	EXPECT_EQ(1, BSK4_test_namespace::i2c_read(HW_BSK_PIN_COUNTER, 0,0, &data, 1));
	EXPECT_EQ(3, data);
}
