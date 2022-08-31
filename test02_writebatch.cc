#include "leveldb/db.h"
#include "leveldb/write_batch.h"
#include "stopwatch.h"
#include <iostream>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
    leveldb::DB *db = nullptr;
    leveldb::Options opts;
    opts.create_if_missing = true;
    opts.error_if_exists = false;
    opts.write_buffer_size = 512 * 1024; // aka 512KB
    opts.compression = leveldb::CompressionType::kNoCompression;

    auto s = leveldb::DB::Open(opts, "./TESTDB_02", &db);
    if (!s.ok())
    {
        abort();
    }

    // sync: 20ms
    // not sync: 10ms
    leveldb::WriteOptions wrtOpts;
    wrtOpts.sync = false;

    char buf[1024] = {'0'};

    tools::StopWatch wat__;
    leveldb::WriteBatch batch;
    for (int i = 0; i < 10000; i++)
    {
        sprintf(buf, "key_%08d", i);
        batch.Put(buf, "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaX");
    }

    s = db->Write(wrtOpts, &batch);
    if (!s.ok())
    {
        std::cout << s.ToString() << std::endl;
        std::abort();
    }
    return 0;
}