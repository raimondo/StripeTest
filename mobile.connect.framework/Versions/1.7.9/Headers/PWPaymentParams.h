//
// PAYWORKS GMBH ("COMPANY") CONFIDENTIAL
// Copyright (c) 2012 payworks GmbH, All Rights Reserved.
//
// NOTICE:  All information contained herein is, and remains the property of COMPANY. The intellectual and technical concepts contained 
// herein are proprietary to COMPANY and may be covered by European or foreign Patents, patents in process, and are protected by trade secret or copyright law.
// Dissemination of this information or reproduction of this material is strictly forbidden unless prior written permission is obtained
// from COMPANY.  Access to the source code contained herein is hereby forbidden to anyone except current COMPANY employees, managers or contractors who have executed
// Confidentiality and Non-disclosure agreements explicitly covering such access.
//
// The copyright notice above does not evidence any actual or intended publication or disclosure  of  this source code, which includes 
// information that is confidential and/or proprietary, and is a trade secret, of  COMPANY.   
// ANY REPRODUCTION, MODIFICATION, DISTRIBUTION, PUBLIC  PERFORMANCE,
// OR PUBLIC DISPLAY OF OR THROUGH USE  OF THIS  SOURCE CODE  WITHOUT  THE EXPRESS WRITTEN CONSENT OF COMPANY IS STRICTLY PROHIBITED, AND IN VIOLATION OF APPLICABLE
// LAWS AND INTERNATIONAL TREATIES.  THE RECEIPT OR POSSESSION OF  THIS SOURCE CODE AND/OR RELATED INFORMATION DOES NOT CONVEY OR IMPLY ANY RIGHTS 
// TO REPRODUCE, DISCLOSE OR DISTRIBUTE ITS CONTENTS, OR TO MANUFACTURE, USE, OR SELL ANYTHING THAT IT  MAY DESCRIBE, IN WHOLE OR IN PART.

#import <Foundation/Foundation.h>

/**
 * Class to encapsulate the parameters needed for performing payments
 *
 * @warning Do not subclass directly. Each type of transaction (credit card etc.) will use its own subclass of PWPaymentParams.
 */

// enum containing the different currencies
typedef enum {
    AED = 0, // United Arab Emirates dirham
    AFN, // Afghanistan Afghani
    ALL, // Albania Lek
    AMD, // Armenia Dram
    ANG, // Netherlands Antilles Guilder
    AOA, // Angola Kwanza
    ARS, // Argentina Peso
    AUD, // Australia Dollar
    AWG, // Aruba Guilder
    AZN, // Azerbaijan New Manat
    BAM, // Bosnia and Herzegovina Convertible Marka
    BBD, // Barbados Dollar
    BDT, // Bangladesh Taka
    BGN, // Bulgaria Lev
    BHD, // Bahrain Dinar
    BIF, // Burundi Franc
    BMD, // Burmuda Dollar
    BND, // Brune Darussalam Dollar
    BOB, // Bolivia Boliviano
    BRL, // Brazil Real
    //BSD, // Bahamas Dollar
    BTN, // Bhutan Ngultrum
    BWP, // Botswana Pula
    BYR, // Belarus Ruble
    BZD, // Belize Dollar
    CAD, // Canadian Dollar
    CDF, // Congo/Kinshasa Franc
    CHF, // Switzerland Franc
    CLP, // Chile Peso
    CNY, // China Yuan Renminbi
    COP, // Colombia Peso
    CRC, // Costa Rica Colon
    CUC, // Cuba Convertible Peso
    CUP, // Cuba Peso
    CVE, // Cape Verde Escudo
    CZK, // Czech Republic Koruna
    DJF, // Djibouti Franc
    DKK, // Denmark Krone
    DOP, // Dominican Republic Peso
    DZD, // Algeria Dinar
    EGP, // Egypt Pound
    ERN, // Eritrea Nakfa
    ETB, // Ethiopia Birr
    EUR, // Euro Member Countries
    FJD, // Fiji Dollar
    FKP, // Falkland Islands (Malvinas) Pound
    GBP, // United Kingdom Pound
    GEL, // Georgia Lari
    GGP, // Guernsey Pound
    GHS, // Ghana Cedi
    GIP, // Gibraltar Pound
    GMD, // Gambia Dalasi
    GNF, // Guinea Franc
    GTQ, // Guetamala Quetzal
    GYD, // Guyana Dollar
    HKD, // Hong Kong Dollar
    HNL, // Honduras Lempira
    HRK, // Croatia Kuna
    HTG, // Haiti Gourde
    HUF, // Hungary Forint
    IDR, // Indonesia Rupiah
    ILS, // Israel Shekel
    IsleMP, // Isle of Man Pound
    INR, // India Rupee
    IQD, // Iraq Dinar
    IRR, // Iran Rial
    ISK, // Iceland Krona
    JEP, // Jersey Pound
    JMD, // Jamaica Dollar
    JOD, // Jordan Dinar
    JPY, // Japan Yen
    KES, // Kenya Shilling
    KGS, // Kyrgyztan Som
    KHR, // Cambodia Riel
    KMF, // Comoros Franc
    KPW, // Korea (North) Won
    KRW, // Korea (South) Won
    KWD, // Kuwait Dinar
    KYD, // Cayman Islands Dollar
    KZT, // Kazakhstan Tenge
    LAK, // Laos Kip
    LBP, // Lebanon Pound
    LKR, // Sri Lanka Rupee
    LRD, // Liberia Dollar
    LSL, // Lesotho Loti
    LYD, // Libya Dinar
    MAD, // Morocco Dirham
    MDL, // Moldova Leu
    MGA, // Madagascar Ariary
    MKD, // Macedonia Denar
    MMK, // Myanmar (Burma) Kyat
    MNT, // Mongolia Tughrik
    MOP, // Macau Pataca
    MRO, // Mauritania Ouguiya
    MUR, // Mauritius Rupee
    MVR, // Maldives (Maldive Islands) Rufiyaa
    MWK, // Malawi Kwacha
    MXN, // Mexico Peso
    MYR, // Malaysia Ringgit
    MZN, // Mozambique Metical
    NAD, // Namibia Dollar
    NGN, // Nigeria Naira
    NIO, // Nicaragua Cordoba
    NOK, // Norway Krone
    NPR, // Nepal Rupee
    NZD, // New Zealand Dollar
    OMR, // Oman Rial
    PAB, // Panama Balboa
    PEN, // Peru Nuevo Sol
    PGK, // Papua New Guinea Kina
    PHP, // Philippines Peso
    PKR, // Pagistan Rupee
    PLN, // Poland Zloty
    PYG, // Paraguay Guarani
    QAR, // Qatar Riyal
    RON, // Romania New Leu
    RSD, // Serbia Dinar
    RUB, // Russia Ruble
    RWF, // Rwanda Franc
    SAR, // Saudi Arabia Riyal
    SBD, // Solomon Islands Dollar
    SCR, // Seychelles Rupee
    SDG, // Sudan Pound
    SEK, // Sweden Krona
    SGD, // Singapore Dollar
    SHP, // Saint Helena Pound
    SLL, // Sierra Leone Leone
    SOS, // Somalia Shilling
    SRD, // Suriname Dollar
    STD, // São Tomé and Príncipe Dobra
    SVC, // El Salvador Colon
    SYP, // Syria Pound
    SZL, // Swaziland Lilangeni
    THB, // Thailand Baht
    TJS, // Tajikistan Somoni
    TMT, // Turkmenistan Manat
    TND, // Tunisia Dinar
    TOP, // Tonga Pa'anga
    TRY, // Turkey Lira
    TTD, // Trinidad and Tobago Dollar
    TVD, // Tuvalu Dollar
    TWD, // Taiwan New Dollar
    TZS, // Tanzania Shilling
    UAH, // Ukraine Hryvnia
    UGX, // Uganda Shilling
    USD, // United States Dollar
    UYU, // Uruguay Peso
    UZS, // Uzbekistan Som
    VEF, // Venezuela Bolivar
    VND, // Vietnam Dong
    VUV, // Vanuatu Vatu
    WST, // Samoa Tala
    XAF, // Communauté Financière Africaine (BEAC) CFA Franc BEAC
    XCD, // East Caribbean Dollar
    XDR, // International Monetary Fund (IMF) Special Drawing Rights
    XOF, // Communauté Financière Africaine (BCEAO) Franc
    XPF, // Comptoirs Français du Pacifique (CFP) Franc
    YER, // Yemen Rial
    ZAR, // South Africa Rand
    ZMW, // Zambia Kwacha
    ZWD, // Zimbabwe Dollar
} PWCurrency;

// enum containing the different capture methods for payment details
typedef enum {
    PWUnknownCaptureMethod,
    PWManualEntry,
} PWCaptureMethod;

@interface PWPaymentParams : NSObject

/** @name Properties */
/** A property that can be set with a custom transaction ID. It is stored together with the transaction for later reference (optional). */
@property (nonatomic, strong) NSString *customIdentifier;
/** The subject of the transaction (optional). This can be empty and will be cut if it is longer than 100 characters.*/
@property (nonatomic, strong) NSString *subject;
/** The amount of the transaction in the specified currency */
@property (nonatomic) double amount;
/** The currency used.  */
@property (nonatomic) PWCurrency currency;
/** @name Properties for Risk Checks (optional) */
/** The given name of the holder */
@property (nonatomic, strong) NSString *givenName;
/** The family name of the holder */
@property (nonatomic, strong) NSString *familyName;
/** Address of the holder: Street name and number */
@property (nonatomic, strong) NSString *street;
/** Address of the holder: zip code */
@property (nonatomic, strong) NSString *zip;
/** Address of the holder: City */
@property (nonatomic, strong) NSString *city;
/** Address of the holder: State */
@property (nonatomic, strong) NSString *state;
/** Address of the holder: Country, according to ISO 3166-1 */
@property (nonatomic, strong) NSString *countryCode;
/** E-mail Address of the holder  */
@property (nonatomic, strong) NSString *email;
/** IP Address of the holder */
@property (nonatomic, strong) NSString *IPaddress;

/** @name Criterions (optional) */
/** Additional Data that you would like to send with a transaction, in a key-value format.
 */
@property (nonatomic, strong) NSDictionary *criterions;

/** @name Geo location properties (optional) */
/** The latitude of the transaction in degrees. Same format as CLLocationCoordinate2D.latitude. I.e. The latitude in degrees. Positive values indicate latitudes north of the equator. Negative values indicate latitudes south of the equator.*/
@property (nonatomic) double latitude;
/** The longitude in degrees. Measurements are relative to the zero meridian, with positive values extending east of the meridian and negative values extending west of the meridian. */
@property (nonatomic) double longitude;
/** The radius of uncertainty for the location, measured in meters. (Same format as  CLLocation.horizontalAccuracy)*/
@property (nonatomic) double horizontalAccuracy;

/** The way the payment paramters have been captured. */
@property (nonatomic) PWCaptureMethod captureMethod;

/** Helper method to add a criterion */
-(void)addCriterionWithKey:(NSString *)key value:(NSString *)value;

/** Helper method to convert PWCurrency to string 
 * @param currency currency to converted to string
 */
+(NSString *) currencyString:(PWCurrency) currency;
/** Helper method to convert String to PWCurrency 
 * @param currency String description of the currency
 */
+(PWCurrency) currencyEnum:(NSString *) currency;
/** Helper method to convert PWCaptureMethod to string 
 * @param captureMethod PWCaptureMethod to converted to string
 */
+(NSString *) captureMethodString:(PWCaptureMethod) captureMethod;

@end
