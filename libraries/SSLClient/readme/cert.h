#ifndef _CERTIFICATES_H_
#define _CERTIFICATES_H_

#ifdef __cplusplus
extern "C"
{
#endif

/* This file is auto-generated by the pycert_bearssl tool.  Do not change it manually.
 * Certificates are BearSSL br_x509_trust_anchor format.  Included certs:
 *
 * Index:    0
 * Label:    VeriSign Class 3 Public Primary Certification Authority - G5
 * Subject:  C=US,O=VeriSign\, Inc.,OU=VeriSign Trust Network,OU=(c) 2006 VeriSign\, Inc. - For authorized use only,CN=VeriSign Class 3 Public Primary Certification Authority - G5
 * Domain(s): www.amazon.com
 */

#define TAs_NUM 1

static const unsigned char TA_DN0[] = {
    0x30, 0x81, 0xca, 0x31, 0x0b, 0x30, 0x09, 0x06, 0x03, 0x55, 0x04, 0x06,
    0x13, 0x02, 0x55, 0x53, 0x31, 0x17, 0x30, 0x15, 0x06, 0x03, 0x55, 0x04,
    0x0a, 0x13, 0x0e, 0x56, 0x65, 0x72, 0x69, 0x53, 0x69, 0x67, 0x6e, 0x2c,
    0x20, 0x49, 0x6e, 0x63, 0x2e, 0x31, 0x1f, 0x30, 0x1d, 0x06, 0x03, 0x55,
    0x04, 0x0b, 0x13, 0x16, 0x56, 0x65, 0x72, 0x69, 0x53, 0x69, 0x67, 0x6e,
    0x20, 0x54, 0x72, 0x75, 0x73, 0x74, 0x20, 0x4e, 0x65, 0x74, 0x77, 0x6f,
    0x72, 0x6b, 0x31, 0x3a, 0x30, 0x38, 0x06, 0x03, 0x55, 0x04, 0x0b, 0x13,
    0x31, 0x28, 0x63, 0x29, 0x20, 0x32, 0x30, 0x30, 0x36, 0x20, 0x56, 0x65,
    0x72, 0x69, 0x53, 0x69, 0x67, 0x6e, 0x2c, 0x20, 0x49, 0x6e, 0x63, 0x2e,
    0x20, 0x2d, 0x20, 0x46, 0x6f, 0x72, 0x20, 0x61, 0x75, 0x74, 0x68, 0x6f,
    0x72, 0x69, 0x7a, 0x65, 0x64, 0x20, 0x75, 0x73, 0x65, 0x20, 0x6f, 0x6e,
    0x6c, 0x79, 0x31, 0x45, 0x30, 0x43, 0x06, 0x03, 0x55, 0x04, 0x03, 0x13,
    0x3c, 0x56, 0x65, 0x72, 0x69, 0x53, 0x69, 0x67, 0x6e, 0x20, 0x43, 0x6c,
    0x61, 0x73, 0x73, 0x20, 0x33, 0x20, 0x50, 0x75, 0x62, 0x6c, 0x69, 0x63,
    0x20, 0x50, 0x72, 0x69, 0x6d, 0x61, 0x72, 0x79, 0x20, 0x43, 0x65, 0x72,
    0x74, 0x69, 0x66, 0x69, 0x63, 0x61, 0x74, 0x69, 0x6f, 0x6e, 0x20, 0x41,
    0x75, 0x74, 0x68, 0x6f, 0x72, 0x69, 0x74, 0x79, 0x20, 0x2d, 0x20, 0x47,
    0x35,
};

static const unsigned char TA_RSA_N0[] = {
    0xaf, 0x24, 0x08, 0x08, 0x29, 0x7a, 0x35, 0x9e, 0x60, 0x0c, 0xaa, 0xe7,
    0x4b, 0x3b, 0x4e, 0xdc, 0x7c, 0xbc, 0x3c, 0x45, 0x1c, 0xbb, 0x2b, 0xe0,
    0xfe, 0x29, 0x02, 0xf9, 0x57, 0x08, 0xa3, 0x64, 0x85, 0x15, 0x27, 0xf5,
    0xf1, 0xad, 0xc8, 0x31, 0x89, 0x5d, 0x22, 0xe8, 0x2a, 0xaa, 0xa6, 0x42,
    0xb3, 0x8f, 0xf8, 0xb9, 0x55, 0xb7, 0xb1, 0xb7, 0x4b, 0xb3, 0xfe, 0x8f,
    0x7e, 0x07, 0x57, 0xec, 0xef, 0x43, 0xdb, 0x66, 0x62, 0x15, 0x61, 0xcf,
    0x60, 0x0d, 0xa4, 0xd8, 0xde, 0xf8, 0xe0, 0xc3, 0x62, 0x08, 0x3d, 0x54,
    0x13, 0xeb, 0x49, 0xca, 0x59, 0x54, 0x85, 0x26, 0xe5, 0x2b, 0x8f, 0x1b,
    0x9f, 0xeb, 0xf5, 0xa1, 0x91, 0xc2, 0x33, 0x49, 0xd8, 0x43, 0x63, 0x6a,
    0x52, 0x4b, 0xd2, 0x8f, 0xe8, 0x70, 0x51, 0x4d, 0xd1, 0x89, 0x69, 0x7b,
    0xc7, 0x70, 0xf6, 0xb3, 0xdc, 0x12, 0x74, 0xdb, 0x7b, 0x5d, 0x4b, 0x56,
    0xd3, 0x96, 0xbf, 0x15, 0x77, 0xa1, 0xb0, 0xf4, 0xa2, 0x25, 0xf2, 0xaf,
    0x1c, 0x92, 0x67, 0x18, 0xe5, 0xf4, 0x06, 0x04, 0xef, 0x90, 0xb9, 0xe4,
    0x00, 0xe4, 0xdd, 0x3a, 0xb5, 0x19, 0xff, 0x02, 0xba, 0xf4, 0x3c, 0xee,
    0xe0, 0x8b, 0xeb, 0x37, 0x8b, 0xec, 0xf4, 0xd7, 0xac, 0xf2, 0xf6, 0xf0,
    0x3d, 0xaf, 0xdd, 0x75, 0x91, 0x33, 0x19, 0x1d, 0x1c, 0x40, 0xcb, 0x74,
    0x24, 0x19, 0x21, 0x93, 0xd9, 0x14, 0xfe, 0xac, 0x2a, 0x52, 0xc7, 0x8f,
    0xd5, 0x04, 0x49, 0xe4, 0x8d, 0x63, 0x47, 0x88, 0x3c, 0x69, 0x83, 0xcb,
    0xfe, 0x47, 0xbd, 0x2b, 0x7e, 0x4f, 0xc5, 0x95, 0xae, 0x0e, 0x9d, 0xd4,
    0xd1, 0x43, 0xc0, 0x67, 0x73, 0xe3, 0x14, 0x08, 0x7e, 0xe5, 0x3f, 0x9f,
    0x73, 0xb8, 0x33, 0x0a, 0xcf, 0x5d, 0x3f, 0x34, 0x87, 0x96, 0x8a, 0xee,
    0x53, 0xe8, 0x25, 0x15,
};

static const unsigned char TA_RSA_E0[] = {
    0x01, 0x00, 0x01,
};

static const br_x509_trust_anchor TAs[] = {
    {
        { (unsigned char *)TA_DN0, sizeof TA_DN0 },
        BR_X509_TA_CA,
        {
            BR_KEYTYPE_RSA,
            { .rsa = {
                (unsigned char *)TA_RSA_N0, sizeof TA_RSA_N0,
                (unsigned char *)TA_RSA_E0, sizeof TA_RSA_E0,
            } }
        }
    },
};

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* ifndef _CERTIFICATES_H_ */