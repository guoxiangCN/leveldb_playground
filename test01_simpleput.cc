#include "leveldb/db.h"
#include <iostream>
#include <stdio.h>
#include <string.h>
#include "stopwatch.h"

int main(int argc, char **argv)
{
    leveldb::DB *db = nullptr;
    leveldb::Options opts;
    opts.create_if_missing = true;
    opts.error_if_exists = false;
    opts.write_buffer_size = 512 * 1024; // aka 512KB
    opts.compression = leveldb::CompressionType::kNoCompression;

    auto s = leveldb::DB::Open(opts, "./TESTDB_01", &db);
    if (!s.ok())
    {
        abort();
    }

    // 1w次写入, 不sync共计耗时87ms
    // 1w次写入, 每次sync共计耗时74s
    leveldb::WriteOptions wrtOpts;
    wrtOpts.sync = true;

    char buf[1024] = {'0'};

    tools::StopWatch wat__;
    for (int i = 0; i < 10000; i++)
    {
        sprintf(buf, "key_%08d", i);
        s = db->Put(wrtOpts, buf, "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaX");
        if (!s.ok())
        {
            std::cout << s.ToString() << std::endl;
            std::abort();
        }
    }

    return 0;
}