﻿/*
* Copyright 2010-2017 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* Licensed under the Apache License, Version 2.0 (the "License").
* You may not use this file except in compliance with the License.
* A copy of the License is located at
*
*  http://aws.amazon.com/apache2.0
*
* or in the "license" file accompanying this file. This file is distributed
* on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
* express or implied. See the License for the specific language governing
* permissions and limitations under the License.
*/

#include <aws/s3/model/CreateMultipartUploadResult.h>
#include <aws/core/utils/xml/XmlSerializer.h>
#include <aws/core/AmazonWebServiceResult.h>
#include <aws/core/utils/StringUtils.h>
#include <aws/core/utils/memory/stl/AWSStringStream.h>

#include <utility>

using namespace Aws::S3::Model;
using namespace Aws::Utils::Xml;
using namespace Aws::Utils;
using namespace Aws;

CreateMultipartUploadResult::CreateMultipartUploadResult() : 
    m_serverSideEncryption(ServerSideEncryption::NOT_SET),
    m_requestCharged(RequestCharged::NOT_SET)
{
}

CreateMultipartUploadResult::CreateMultipartUploadResult(const Aws::AmazonWebServiceResult<XmlDocument>& result) : 
    m_serverSideEncryption(ServerSideEncryption::NOT_SET),
    m_requestCharged(RequestCharged::NOT_SET)
{
  *this = result;
}

CreateMultipartUploadResult& CreateMultipartUploadResult::operator =(const Aws::AmazonWebServiceResult<XmlDocument>& result)
{
  const XmlDocument& xmlDocument = result.GetPayload();
  XmlNode resultNode = xmlDocument.GetRootElement();

  if(!resultNode.IsNull())
  {
    XmlNode bucketNode = resultNode.FirstChild("Bucket");
    if(!bucketNode.IsNull())
    {
      m_bucket = StringUtils::Trim(bucketNode.GetText().c_str());
    }
    XmlNode keyNode = resultNode.FirstChild("Key");
    if(!keyNode.IsNull())
    {
      m_key = StringUtils::Trim(keyNode.GetText().c_str());
    }
    XmlNode uploadIdNode = resultNode.FirstChild("UploadId");
    if(!uploadIdNode.IsNull())
    {
      m_uploadId = StringUtils::Trim(uploadIdNode.GetText().c_str());
    }
  }

  const auto& headers = result.GetHeaderValueCollection();
  const auto& abortDateIter = headers.find("x-amz-abort-date");
  if(abortDateIter != headers.end())
  {
    m_abortDate = DateTime(abortDateIter->second, DateFormat::RFC822);
  }

  const auto& abortRuleIdIter = headers.find("x-amz-abort-rule-id");
  if(abortRuleIdIter != headers.end())
  {
    m_abortRuleId = abortRuleIdIter->second;
  }

  const auto& serverSideEncryptionIter = headers.find("x-amz-server-side-encryption");
  if(serverSideEncryptionIter != headers.end())
  {
    m_serverSideEncryption = ServerSideEncryptionMapper::GetServerSideEncryptionForName(serverSideEncryptionIter->second);
  }

  const auto& sSECustomerAlgorithmIter = headers.find("x-amz-server-side-encryption-customer-algorithm");
  if(sSECustomerAlgorithmIter != headers.end())
  {
    m_sSECustomerAlgorithm = sSECustomerAlgorithmIter->second;
  }

  const auto& sSECustomerKeyMD5Iter = headers.find("x-amz-server-side-encryption-customer-key-md5");
  if(sSECustomerKeyMD5Iter != headers.end())
  {
    m_sSECustomerKeyMD5 = sSECustomerKeyMD5Iter->second;
  }

  const auto& sSEKMSKeyIdIter = headers.find("x-amz-server-side-encryption-aws-kms-key-id");
  if(sSEKMSKeyIdIter != headers.end())
  {
    m_sSEKMSKeyId = sSEKMSKeyIdIter->second;
  }

  const auto& sSEKMSEncryptionContextIter = headers.find("x-amz-server-side-encryption-context");
  if(sSEKMSEncryptionContextIter != headers.end())
  {
    m_sSEKMSEncryptionContext = sSEKMSEncryptionContextIter->second;
  }

  const auto& requestChargedIter = headers.find("x-amz-request-charged");
  if(requestChargedIter != headers.end())
  {
    m_requestCharged = RequestChargedMapper::GetRequestChargedForName(requestChargedIter->second);
  }

  return *this;
}
