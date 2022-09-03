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

    auto s = leveldb::DB::Open(opts, "./TESTDB_03", &db);
    if (!s.ok())
    {
        abort();
    }

    leveldb::WriteOptions wrtOpts;
    wrtOpts.sync = false;

    char buf[1024] = {'0'};

    tools::StopWatch wat__;
    for (int i = 0; i < 100000; i++)
    {
        memset(buf, 0, sizeof(buf));
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