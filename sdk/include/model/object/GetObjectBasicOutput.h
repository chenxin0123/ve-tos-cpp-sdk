#pragma once

#include "model/RequestInfo.h"
#include "TosResponse.h"
#include "Type.h"

namespace VolcengineTos {
class GetObjectBasicOutput {
public:
    void fromResponse(TosResponse& res);
    //    bool operator==(const GetObjectBasicOutput& rhs) const;
    //    bool operator!=(const GetObjectBasicOutput& rhs) const;

    const RequestInfo& getRequestInfo() const {
        return requestInfo_;
    }
    void setRequestInfo(const RequestInfo& requestinfo) {
        requestInfo_ = requestinfo;
    }
    const std::string& getContentRange() const {
        return contentRange_;
    }
    void setContentRange(const std::string& contentrange) {
        contentRange_ = contentrange;
    }
    const std::string& getETags() const {
        return eTag_;
    }
    void setETags(const std::string& etags) {
        eTag_ = etags;
    }
    const std::string& getETag() const {
        return eTag_;
    }
    void setETag(const std::string& eTag) {
        eTag_ = eTag;
    }
    time_t getLastModified() const {
        return lastModified_;
    }
    void setLastModified(time_t lastmodified) {
        lastModified_ = lastmodified;
    }
    bool isDeleteMarker() const {
        return deleteMarker_;
    }
    void setDeleteMarker(bool deletemarker) {
        deleteMarker_ = deletemarker;
    }
    const std::string& getSsecAlgorithm() const {
        return ssecAlgorithm_;
    }
    void setSsecAlgorithm(const std::string& ssecalgorithm) {
        ssecAlgorithm_ = ssecalgorithm;
    }
    const std::string& getSsecKeyMd5() const {
        return ssecKeyMD5_;
    }
    void setSsecKeyMd5(const std::string& sseckeymd5) {
        ssecKeyMD5_ = sseckeymd5;
    }
    const std::string& getVersionId() const {
        return versionID_;
    }
    void setVersionId(const std::string& versionid) {
        versionID_ = versionid;
    }
    const std::string& getWebsiteRedirectLocation() const {
        return websiteRedirectLocation_;
    }
    void setWebsiteRedirectLocation(const std::string& websiteredirectlocation) {
        websiteRedirectLocation_ = websiteredirectlocation;
    }
    const std::string& getObjectType() const {
        return objectType_;
    }
    void setObjectType(const std::string& objecttype) {
        objectType_ = objecttype;
    }
    uint64_t getHashCrc64Ecma() const {
        return hashCrc64ecma_;
    }
    void setHashCrc64Ecma(uint64_t hashcrc64ecma) {
        hashCrc64ecma_ = hashcrc64ecma;
    }
    StorageClassType getStorageClass() const {
        return storageClass_;
    }
    void setStorageClass(StorageClassType storageclass) {
        storageClass_ = storageclass;
    }
    const std::map<std::string, std::string>& getMeta() const {
        return meta_;
    }
    void setMeta(const std::map<std::string, std::string>& meta) {
        meta_ = meta;
    }
    int64_t getContentLength() const {
        return contentLength_;
    }
    void setContentLength(int64_t contentlength) {
        contentLength_ = contentlength;
    }
    const std::string& getContentType() const {
        return contentType_;
    }
    void setContentType(const std::string& contenttype) {
        contentType_ = contenttype;
    }
    const std::string& getCacheControl() const {
        return cacheControl_;
    }
    void setCacheControl(const std::string& cachecontrol) {
        cacheControl_ = cachecontrol;
    }
    const std::string& getContentDisposition() const {
        return contentDisposition_;
    }
    void setContentDisposition(const std::string& contentdisposition) {
        contentDisposition_ = contentdisposition;
    }
    const std::string& getContentEncoding() const {
        return contentEncoding_;
    }
    void setContentEncoding(const std::string& contentencoding) {
        contentEncoding_ = contentencoding;
    }
    const std::string& getContentLanguage() const {
        return contentLanguage_;
    }
    void setContentLanguage(const std::string& contentlanguage) {
        contentLanguage_ = contentlanguage;
    }
    time_t getExpires() const {
        return expires_;
    }
    void setExpires(time_t expires) {
        expires_ = expires;
    }

private:
    RequestInfo requestInfo_;

    std::string contentRange_;
    std::string eTag_;
    std::time_t lastModified_ = 0;
    bool deleteMarker_ = 0;
    std::string ssecAlgorithm_;
    std::string ssecKeyMD5_;
    std::string versionID_;
    std::string websiteRedirectLocation_;
    std::string objectType_;
    uint64_t hashCrc64ecma_ = 0;
    StorageClassType storageClass_ = StorageClassType::NotSet;
    std::map<std::string, std::string> meta_;

    int64_t contentLength_ = 0;
    std::string contentType_;
    std::string cacheControl_;
    std::string contentDisposition_;
    std::string contentEncoding_;
    std::string contentLanguage_;
    std::time_t expires_ = 0;
};
}  // namespace VolcengineTos
