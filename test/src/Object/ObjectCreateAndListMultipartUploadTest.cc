#include "../TestConfig.h"
#include "../Utils.h"
#include "TosClientV2.h"
#include <gtest/gtest.h>

namespace VolcengineTos {
class ObjectCreateAndListMultipartUploadTest : public ::testing::Test {
protected:
    ObjectCreateAndListMultipartUploadTest() {
    }

    ~ObjectCreateAndListMultipartUploadTest() override {
    }

    static void SetUpTestCase() {
        ClientConfig conf;
        conf.endPoint = TestConfig::Endpoint;
        cliV2 = std::make_shared<TosClientV2>(TestConfig::Region, TestConfig::Ak, TestConfig::Sk, conf);
        bkt_name = TestUtils::GetBucketName(TestConfig::TestPrefix);
        obj_name = TestUtils::GetObjectKey(TestConfig::TestPrefix);
        TestUtils::CreateBucket(cliV2, bkt_name);
    }

    // Tears down the stuff shared by all tests in this test case.
    static void TearDownTestCase() {
        TestUtils::CleanBucket(cliV2, bkt_name);
        cliV2 = nullptr;
    }

public:
    static std::shared_ptr<TosClientV2> cliV2;
    static std::string bkt_name;
    static std::string obj_name;
};

std::shared_ptr<TosClientV2> ObjectCreateAndListMultipartUploadTest::cliV2 = nullptr;
std::string ObjectCreateAndListMultipartUploadTest::bkt_name = "";
std::string ObjectCreateAndListMultipartUploadTest::obj_name = "";

TEST_F(ObjectCreateAndListMultipartUploadTest, CreateListMultipartUploadTest) {
    CreateMultipartUploadInput input_multipart_create(bkt_name, obj_name);
    std::map<std::string, std::string> meta_;
    for (int i = 0; i < 100; ++i) {
        std::stringstream ss;
        ss << std::setw(3) << std::setfill('0') << i;
        std::string idx_string;
        ss >> idx_string;
        input_multipart_create.setKey(idx_string);
        meta_["self-test"] = idx_string;
        input_multipart_create.setMeta(meta_);
        auto upload = cliV2->createMultipartUpload(input_multipart_create);
    }
    ListMultipartUploadsV2Input input_multipart_list(bkt_name);
    input_multipart_list.setMaxUploads(10);
    std::string start_marker = "";
    std::string next_marker = "";
    int i = 0;
    for (int t = 0; t < 10; ++t) {
        next_marker = start_marker;

        input_multipart_list.setKeyMarker(next_marker);
        auto output = cliV2->listMultipartUploads(input_multipart_list);
        EXPECT_EQ(output.isSuccess(), true);
        start_marker = output.result().getNextKeyMarker();
        auto uploads = output.result().getUploads();
        for (int p = 0; p < 10; ++p) {
            std::stringstream ss;
            ss << std::setw(3) << std::setfill('0') << i;
            std::string idx_string;
            ss >> idx_string;
            bool check_upload_part_name = (uploads[p].getKey() == idx_string);
            EXPECT_EQ(check_upload_part_name, true);
            i++;
        }
    }
}
TEST_F(ObjectCreateAndListMultipartUploadTest, AbortMultipartUploadTest) {
    std::string bkt_name_ = TestUtils::GetBucketName(TestConfig::TestPrefix);
    TestUtils::CreateBucket(cliV2, bkt_name_);
    CreateMultipartUploadInput input_multipart_create(bkt_name_, "test-obj-001");
    auto upload_1 = cliV2->createMultipartUpload(input_multipart_create);
    input_multipart_create.setKey("test-obj-002");
    auto upload_2 = cliV2->createMultipartUpload(input_multipart_create);
    AbortMultipartUploadInput input_1(bkt_name_, "test-obj-001", upload_1.result().getUploadId());
    AbortMultipartUploadInput input_2(bkt_name_, "test-obj-002", upload_2.result().getUploadId());
    ListMultipartUploadsV2Input input_multipart_list(bkt_name_);
    auto output_list_1 = cliV2->listMultipartUploads(input_multipart_list);
    EXPECT_EQ(output_list_1.isSuccess(), true);
    EXPECT_EQ(output_list_1.result().getUploads().size(), 2);

    auto output_abort_1 = cliV2->abortMultipartUpload(input_1);
    EXPECT_EQ(output_abort_1.isSuccess(), true);
    auto output_abort_2 = cliV2->abortMultipartUpload(input_2);
    EXPECT_EQ(output_abort_2.isSuccess(), true);

    auto output_list_2 = cliV2->listMultipartUploads(input_multipart_list);
    EXPECT_EQ(output_list_2.isSuccess(), true);
    EXPECT_EQ(output_list_2.result().getUploads().size(), 0);
    TestUtils::CleanBucket(cliV2, bkt_name_);
}

TEST_F(ObjectCreateAndListMultipartUploadTest, ListObjectWith3PrefixObjectsTest) {
    std::string bkt_name_ = TestUtils::GetBucketName(TestConfig::TestPrefix);
    TestUtils::CreateBucket(cliV2, bkt_name_);
    CreateMultipartUploadInput input_multipart_create(bkt_name_, obj_name);
    std::string obj_name_1 = "11/22/33/4444";
    input_multipart_create.setKey(obj_name_1);
    auto upload_1 = cliV2->createMultipartUpload(input_multipart_create);
    std::string obj_name_2 = "11/22/34/4444";
    input_multipart_create.setKey(obj_name_2);
    auto upload_2 = cliV2->createMultipartUpload(input_multipart_create);

    ListMultipartUploadsV2Input input_multipart_list(bkt_name_);
    input_multipart_list.setPrefix("11/22/");
    input_multipart_list.setDelimiter("/");
    auto output = cliV2->listMultipartUploads(input_multipart_list);
    EXPECT_EQ(output.isSuccess(), true);
    EXPECT_EQ(output.result().getCommonPrefixes()[0].getPrefix() == "11/22/33/", true);
    EXPECT_EQ(output.result().getCommonPrefixes()[1].getPrefix() == "11/22/34/", true);
    TestUtils::CleanBucket(cliV2, bkt_name_);
}
TEST_F(ObjectCreateAndListMultipartUploadTest, CreateUploadsFromNonexistentBucketTest) {
    std::string nonexistent_bkt_name = TestUtils::GetBucketName(TestConfig::TestPrefix);
    CreateMultipartUploadInput input_multipart_create(nonexistent_bkt_name, obj_name);
    auto output = cliV2->createMultipartUpload(input_multipart_create);
    EXPECT_EQ(output.isSuccess(), false);
    EXPECT_EQ(output.error().getStatusCode(), 404);
    EXPECT_EQ(output.error().getMessage() == "The specified bucket does not exist.", true);
}
TEST_F(ObjectCreateAndListMultipartUploadTest, ListUploadsFromNonexistentBucketTest) {
    std::string nonexistent_bkt_name = TestUtils::GetBucketName(TestConfig::TestPrefix);
    ListMultipartUploadsV2Input input_multipart_list(nonexistent_bkt_name);

    auto output = cliV2->listMultipartUploads(input_multipart_list);
    EXPECT_EQ(output.isSuccess(), false);
    EXPECT_EQ(output.error().getStatusCode(), 404);
    EXPECT_EQ(output.error().getMessage() == "The specified bucket does not exist.", true);
}
TEST_F(ObjectCreateAndListMultipartUploadTest, AbortUploadsFromNonexistentBucketTest) {
    CreateMultipartUploadInput input_multipart_create(bkt_name, obj_name);
    std::string obj_name_create = "112233";
    input_multipart_create.setKey(obj_name_create);
    auto upload_1 = cliV2->createMultipartUpload(input_multipart_create);
    std::string bkt_name_ = TestUtils::GetBucketName(TestConfig::TestPrefix);
    std::string obj_name_ = TestUtils::GetObjectKey(TestConfig::TestPrefix);
    std::string upload_id = "11edee11aeec61fd11d448f505be2ef3";

    AbortMultipartUploadInput input_multipart_abort(bkt_name_, obj_name_, upload_id);
    auto output_1 = cliV2->abortMultipartUpload(input_multipart_abort);
    EXPECT_EQ(output_1.isSuccess(), false);
    EXPECT_EQ(output_1.error().getStatusCode(), 404);
    EXPECT_EQ(output_1.error().getMessage() == "The specified bucket does not exist.", true);

    input_multipart_abort.setBucket(bkt_name);
    auto output_2 = cliV2->abortMultipartUpload(input_multipart_abort);
    EXPECT_EQ(output_2.isSuccess(), false);
    EXPECT_EQ(output_2.error().getStatusCode(), 404);

    input_multipart_abort.setUploadId(upload_id);
    auto output_3 = cliV2->abortMultipartUpload(input_multipart_abort);
    EXPECT_EQ(output_3.isSuccess(), false);
    EXPECT_EQ(output_3.error().getStatusCode(), 404);
}
}  // namespace VolcengineTos
