#include "CppUnitTest.h"

#include "../headers/logger.hpp"
#include "../headers/memutils.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#pragma comment(lib, "rpcrt4.lib")
#pragma comment(lib, "psapi.lib" )
#pragma comment(lib, "Shlwapi.lib")
#pragma comment(lib, "dhcpcsvc.lib")

namespace MIDIfaceTest
{
	TEST_CLASS(LoggerTest)
	{
	public:
		
		TEST_METHOD(SendDebug)
		{
            char message[64];
            FILE* log_stream = fmemopen(message, 64, "w+");
            char written_message[13];
            memset(written_message, 0x00, 13);

            add_log_output(log_stream, LogLevel::MF_DEBUG);
            send_log(LogLevel::MF_DEBUG, "%s", "test");

            rewind(log_stream);
            memset(written_message, 0x00, 13);
            fread(written_message, 12, 1, log_stream);
            Assert::AreEqual(written_message, "DEBUG: test\n");

            clear_logs_stream();
		}

        TEST_METHOD(SendError)
        {
            char message[64];
            FILE* log_stream = fmemopen(message, 64, "w+");
            char written_message[13];
            memset(written_message, 0x00, 13);

            add_log_output(log_stream, LogLevel::MF_ERROR);
            send_log(LogLevel::MF_ERROR, "%s", "test");

            rewind(log_stream);
            memset(written_message, 0x00, 13);
            fread(written_message, 12, 1, log_stream);
            Assert::AreEqual(written_message, "ERROR: test\n");

            clear_logs_stream();
        }

        TEST_METHOD(SendInfo)
        {
            char message[64];
            FILE* log_stream = fmemopen(message, 64, "w+");
            char written_message[13];
            memset(written_message, 0x00, 13);

            add_log_output(log_stream, LogLevel::MF_INFO);
            send_log(LogLevel::MF_INFO, "%s", "test");

            rewind(log_stream);
            memset(written_message, 0x00, 13);
            fread(written_message, 12, 1, log_stream);
            Assert::AreEqual(written_message, "INFO: test\n");

            clear_logs_stream();
        }

        TEST_METHOD(SendLeveledError)
        {
            char message[64];
            FILE* log_stream = fmemopen(message, 64, "w+");
            char written_message[13];
            memset(written_message, 0x00, 13);

            add_log_output(log_stream, LogLevel::MF_ERROR);

            send_log(LogLevel::MF_DEBUG, "%s", "test");
            rewind(log_stream);
            memset(written_message, 0x00, 13);
            fread(written_message, 12, 1, log_stream);
            Assert::AreNotEqual(written_message, "DEBUG: test\n");

            send_log(LogLevel::MF_INFO, "%s", "test");
            rewind(log_stream);
            memset(written_message, 0x00, 13);
            fread(written_message, 11, 1, log_stream);
            Assert::AreNotEqual(written_message, "INFO: test\n");

            send_log(LogLevel::MF_ERROR, "%s", "test");
            rewind(log_stream);
            memset(written_message, 0x00, 13);
            fread(written_message, 12, 1, log_stream);
            Assert::AreEqual(written_message, "ERROR: test\n");

            clear_logs_stream();
        }

        TEST_METHOD(SendLeveledInfo)
        {
            char message[64];
            FILE* log_stream = fmemopen(message, 64, "w+");
            char written_message[13];
            memset(written_message, 0x00, 13);

            add_log_output(log_stream, LogLevel::MF_INFO);

            send_log(LogLevel::MF_DEBUG, "%s", "test");
            rewind(log_stream);
            memset(written_message, 0x00, 13);
            fread(written_message, 12, 1, log_stream);
            Assert::AreNotEqual(written_message, "DEBUG: test\n");

            send_log(LogLevel::MF_INFO, "%s", "test");
            rewind(log_stream);
            memset(written_message, 0x00, 13);
            fread(written_message, 11, 1, log_stream);
            Assert::AreEqual(written_message, "INFO: test\n");

            send_log(LogLevel::MF_ERROR, "%s", "test");
            fseek(log_stream, -12, SEEK_CUR);
            memset(written_message, 0x00, 13);
            fread(written_message, 12, 1, log_stream);
            Assert::AreEqual(written_message, "ERROR: test\n");

            clear_logs_stream();
        }

        TEST_METHOD(SendLeveledDebug)
        {
            char message[64];
            FILE* log_stream = fmemopen(message, 64, "w+");
            char written_message[13];
            memset(written_message, 0x00, 13);

            add_log_output(log_stream, LogLevel::MF_DEBUG);

            send_log(LogLevel::MF_DEBUG, "%s", "test");
            rewind(log_stream);
            fread(written_message, 12, 1, log_stream);
            Assert::AreEqual(written_message, "DEBUG: test\n");

            send_log(LogLevel::MF_INFO, "%s", "test");
            fseek(log_stream, -11, SEEK_CUR);
            memset(written_message, 0x00, 13);
            fread(written_message, 11, 1, log_stream);
            Assert::AreEqual(written_message, "INFO: test\n");

            send_log(LogLevel::MF_ERROR, "%s", "test");
            fseek(log_stream, -12, SEEK_CUR);
            memset(written_message, 0x00, 13);
            fread(written_message, 12, 1, log_stream);
            Assert::AreEqual(written_message, "ERROR: test\n");

            clear_logs_stream();
        }

        TEST_METHOD(SendMultipleOutputs)
        {
            char message1[64], message2[64];
            FILE* log_stream1 = fmemopen(message1, 64, "w+");
            FILE* log_stream2 = fmemopen(message2, 64, "w+");
            char written_message[13];
            memset(written_message, 0x00, 13);

            add_log_output(log_stream1, LogLevel::MF_DEBUG);
            add_log_output(log_stream2, LogLevel::MF_DEBUG);
            send_log(LogLevel::MF_DEBUG, "%s", "test");

            rewind(log_stream1);
            memset(written_message, 0x00, 13);
            fread(written_message, 11, 1, log_stream1);
            Assert::AreEqual(written_message, "DEBUG: test");
            rewind(log_stream2);
            memset(written_message, 0x00, 13);
            fread(written_message, 11, 1, log_stream2);
            Assert::AreEqual(written_message, "DEBUG: test");

            clear_logs_stream();
        }
    };

    TEST_CLASS(TestMemutils)
    {
    public:

#ifdef _MSC_VER
        TEST_METHOD(WindowsFmemOpen)
        {
            char response[4];

            FILE* memory = fmemopen("test", 4, "r");
            fread(response, 4, 1, memory);

            Assert::AreEqual("test", response);
        }
#endif
    };
}
