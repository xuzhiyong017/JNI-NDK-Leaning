





Internet Engineering Task Force (IETF)                    H. Schulzrinne
Request for Comments: 7826                           Columbia University
Obsoletes: 2326                                                   A. Rao
Category: Standards Track                                          Cisco
ISSN: 2070-1721                                              R. Lanphier

                                                           M. Westerlund
                                                                Ericsson
                                                     M. Stiemerling, Ed.
                                University of Applied Sciences Darmstadt
                                                           December 2016


                Real-Time Streaming Protocol Version 2.0

Abstract

   This memorandum defines the Real-Time Streaming Protocol (RTSP)
   version 2.0, which obsoletes RTSP version 1.0 defined in RFC 2326.

   RTSP is an application-layer protocol for the setup and control of
   the delivery of data with real-time properties.  RTSP provides an
   extensible framework to enable controlled, on-demand delivery of
   real-time data, such as audio and video.  Sources of data can include
   both live data feeds and stored clips.  This protocol is intended to
   control multiple data delivery sessions; provide a means for choosing
   delivery channels such as UDP, multicast UDP, and TCP; and provide a
   means for choosing delivery mechanisms based upon RTP (RFC 3550).

Status of This Memo

   This is an Internet Standards Track document.

   This document is a product of the Internet Engineering Task Force
   (IETF).  It represents the consensus of the IETF community.  It has
   received public review and has been approved for publication by the
   Internet Engineering Steering Group (IESG).  Further information on
   Internet Standards is available in Section 2 of RFC 7841.

   Information about the current status of this document, any errata,
   and how to provide feedback on it may be obtained at
   http://www.rfc-editor.org/info/rfc7826.









Schulzrinne, et al.          Standards Track                    [Page 1]

RFC 7826                        RTSP 2.0                   December 2016


Copyright Notice

   Copyright (c) 2016 IETF Trust and the persons identified as the
   document authors.  All rights reserved.

   This document is subject to BCP 78 and the IETF Trust's Legal
   Provisions Relating to IETF Documents
   (http://trustee.ietf.org/license-info) in effect on the date of
   publication of this document.  Please review these documents
   carefully, as they describe your rights and restrictions with respect
   to this document.  Code Components extracted from this document must
   include Simplified BSD License text as described in Section 4.e of
   the Trust Legal Provisions and are provided without warranty as
   described in the Simplified BSD License.

   This document may contain material from IETF Documents or IETF
   Contributions published or made publicly available before November
   10, 2008.  The person(s) controlling the copyright in some of this
   material may not have granted the IETF Trust the right to allow
   modifications of such material outside the IETF Standards Process.
   Without obtaining an adequate license from the person(s) controlling
   the copyright in such materials, this document may not be modified
   outside the IETF Standards Process, and derivative works of it may
   not be created outside the IETF Standards Process, except to format
   it for publication as an RFC or to translate it into languages other
   than English.

Table of Contents

   1. Introduction ...................................................10
   2. Protocol Overview ..............................................11
      2.1. Presentation Description ..................................12
      2.2. Session Establishment .....................................12
      2.3. Media Delivery Control ....................................14
      2.4. Session Parameter Manipulations ...........................15
      2.5. Media Delivery ............................................16
           2.5.1. Media Delivery Manipulations .......................16
      2.6. Session Maintenance and Termination .......................19
      2.7. Extending RTSP ............................................20
   3. Document Conventions ...........................................21
      3.1. Notational Conventions ....................................21
      3.2. Terminology ...............................................21
   4. Protocol Parameters ............................................25
      4.1. RTSP Version ..............................................25
      4.2. RTSP IRI and URI ..........................................25
      4.3. Session Identifiers .......................................28





Schulzrinne, et al.          Standards Track                    [Page 2]

RFC 7826                        RTSP 2.0                   December 2016


      4.4. Media-Time Formats ........................................28
           4.4.1. SMPTE-Relative Timestamps ..........................28
           4.4.2. Normal Play Time ...................................29
           4.4.3. Absolute Time ......................................30
      4.5. Feature Tags ..............................................31
      4.6. Message Body Tags .........................................32
      4.7. Media Properties ..........................................32
           4.7.1. Random Access and Seeking ..........................33
           4.7.2. Retention ..........................................34
           4.7.3. Content Modifications ..............................34
           4.7.4. Supported Scale Factors ............................34
           4.7.5. Mapping to the Attributes ..........................35
   5. RTSP Message ...................................................35
      5.1. Message Types .............................................36
      5.2. Message Headers ...........................................36
      5.3. Message Body ..............................................37
      5.4. Message Length ............................................37
   6. General-Header Fields ..........................................37
   7. Request ........................................................39
      7.1. Request Line ..............................................40
      7.2. Request-Header Fields .....................................42
   8. Response .......................................................43
      8.1. Status-Line ...............................................43
           8.1.1. Status Code and Reason Phrase ......................43
      8.2. Response Headers ..........................................47
   9. Message Body ...................................................47
      9.1. Message Body Header Fields ................................48
      9.2. Message Body ..............................................49
      9.3. Message Body Format Negotiation ...........................49
   10. Connections ...................................................50
      10.1. Reliability and Acknowledgements .........................50
      10.2. Using Connections ........................................51
      10.3. Closing Connections ......................................54
      10.4. Timing Out Connections and RTSP Messages .................56
      10.5. Showing Liveness .........................................57
      10.6. Use of IPv6 ..............................................58
      10.7. Overload Control .........................................58
   11. Capability Handling ...........................................60
      11.1. Feature Tag: play.basic ..................................62
   12. Pipelining Support ............................................62
   13. Method Definitions ............................................63
      13.1. OPTIONS ..................................................65
      13.2. DESCRIBE .................................................66
      13.3. SETUP ....................................................68
           13.3.1. Changing Transport Parameters .....................71
      13.4. PLAY .....................................................72
           13.4.1. General Usage .....................................72
           13.4.2. Aggregated Sessions ...............................77



Schulzrinne, et al.          Standards Track                    [Page 3]

RFC 7826                        RTSP 2.0                   December 2016


           13.4.3. Updating Current PLAY Requests ....................78
           13.4.4. Playing On-Demand Media ...........................81
           13.4.5. Playing Dynamic On-Demand Media ...................81
           13.4.6. Playing Live Media ................................81
           13.4.7. Playing Live with Recording .......................82
           13.4.8. Playing Live with Time-Shift ......................83
      13.5. PLAY_NOTIFY ..............................................83
           13.5.1. End-of-Stream .....................................84
           13.5.2. Media-Properties-Update ...........................86
           13.5.3. Scale-Change ......................................87
      13.6. PAUSE ....................................................89
      13.7. TEARDOWN .................................................92
           13.7.1. Client to Server ..................................92
           13.7.2. Server to Client ..................................93
      13.8. GET_PARAMETER ............................................94
      13.9. SET_PARAMETER ............................................96
      13.10. REDIRECT ................................................98
   14. Embedded (Interleaved) Binary Data ...........................101
   15. Proxies ......................................................103
      15.1. Proxies and Protocol Extensions .........................104
      15.2. Multiplexing and Demultiplexing of Messages .............105
   16. Caching ......................................................106
      16.1. Validation Model ........................................107
           16.1.1. Last-Modified Dates ..............................108
           16.1.2. Message Body Tag Cache Validators ................108
           16.1.3. Weak and Strong Validators .......................108
           16.1.4. Rules for When to Use Message Body Tags
                   and Last-Modified Dates ..........................110
           16.1.5. Non-validating Conditionals ......................112
      16.2. Invalidation after Updates or Deletions .................112
   17. Status Code Definitions ......................................113
      17.1. Informational 1xx .......................................113
           17.1.1. 100 Continue .....................................113
      17.2. Success 2xx .............................................113
           17.2.1. 200 OK ...........................................113
      17.3. Redirection 3xx .........................................113
           17.3.1. 300 ..............................................114
           17.3.2. 301 Moved Permanently ............................114
           17.3.3. 302 Found ........................................114
           17.3.4. 303 See Other ....................................115
           17.3.5. 304 Not Modified .................................115
           17.3.6. 305 Use Proxy ....................................115
      17.4. Client Error 4xx ........................................116
           17.4.1. 400 Bad Request ..................................116
           17.4.2. 401 Unauthorized .................................116
           17.4.3. 402 Payment Required .............................116
           17.4.4. 403 Forbidden ....................................116
           17.4.5. 404 Not Found ....................................116



Schulzrinne, et al.          Standards Track                    [Page 4]

RFC 7826                        RTSP 2.0                   December 2016


           17.4.6. 405 Method Not Allowed ...........................117
           17.4.7. 406 Not Acceptable ...............................117
           17.4.8. 407 Proxy Authentication Required ................117
           17.4.9. 408 Request Timeout ..............................117
           17.4.10. 410 Gone ........................................118
           17.4.11. 412 Precondition Failed .........................118
           17.4.12. 413 Request Message Body Too Large ..............118
           17.4.13. 414 Request-URI Too Long ........................118
           17.4.14. 415 Unsupported Media Type ......................119
           17.4.15. 451 Parameter Not Understood ....................119
           17.4.16. 452 Illegal Conference Identifier ...............119
           17.4.17. 453 Not Enough Bandwidth ........................119
           17.4.18. 454 Session Not Found ...........................119
           17.4.19. 455 Method Not Valid in This State ..............119
           17.4.20. 456 Header Field Not Valid for Resource .........119
           17.4.21. 457 Invalid Range ...............................120
           17.4.22. 458 Parameter Is Read-Only ......................120
           17.4.23. 459 Aggregate Operation Not Allowed .............120
           17.4.24. 460 Only Aggregate Operation Allowed ............120
           17.4.25. 461 Unsupported Transport .......................120
           17.4.26. 462 Destination Unreachable .....................120
           17.4.27. 463 Destination Prohibited ......................120
           17.4.28. 464 Data Transport Not Ready Yet ................121
           17.4.29. 465 Notification Reason Unknown .................121
           17.4.30. 466 Key Management Error ........................121
           17.4.31. 470 Connection Authorization Required ...........121
           17.4.32. 471 Connection Credentials Not Accepted .........121
           17.4.33. 472 Failure to Establish Secure Connection ......121
      17.5. Server Error 5xx ........................................122
           17.5.1. 500 Internal Server Error ........................122
           17.5.2. 501 Not Implemented ..............................122
           17.5.3. 502 Bad Gateway ..................................122
           17.5.4. 503 Service Unavailable ..........................122
           17.5.5. 504 Gateway Timeout ..............................123
           17.5.6. 505 RTSP Version Not Supported ...................123
           17.5.7. 551 Option Not Supported .........................123
           17.5.8. 553 Proxy Unavailable ............................123
   18. Header Field Definitions .....................................124
      18.1. Accept ..................................................134
      18.2. Accept-Credentials ......................................135
      18.3. Accept-Encoding .........................................135
      18.4. Accept-Language .........................................136
      18.5. Accept-Ranges ...........................................137
      18.6. Allow ...................................................138
      18.7. Authentication-Info .....................................138
      18.8. Authorization ...........................................138
      18.9. Bandwidth ...............................................139
      18.10. Blocksize ..............................................140



Schulzrinne, et al.          Standards Track                    [Page 5]

RFC 7826                        RTSP 2.0                   December 2016


      18.11. Cache-Control ..........................................140
      18.12. Connection .............................................143
      18.13. Connection-Credentials .................................143
      18.14. Content-Base ...........................................144
      18.15. Content-Encoding .......................................145
      18.16. Content-Language .......................................145
      18.17. Content-Length .........................................146
      18.18. Content-Location .......................................146
      18.19. Content-Type ...........................................148
      18.20. CSeq ...................................................148
      18.21. Date ...................................................150
      18.22. Expires ................................................151
      18.23. From ...................................................151
      18.24. If-Match ...............................................152
      18.25. If-Modified-Since ......................................152
      18.26. If-None-Match ..........................................153
      18.27. Last-Modified ..........................................154
      18.28. Location ...............................................154
      18.29. Media-Properties .......................................154
      18.30. Media-Range ............................................156
      18.31. MTag ...................................................157
      18.32. Notify-Reason ..........................................158
      18.33. Pipelined-Requests .....................................158
      18.34. Proxy-Authenticate .....................................159
      18.35. Proxy-Authentication-Info ..............................159
      18.36. Proxy-Authorization ....................................159
      18.37. Proxy-Require ..........................................160
      18.38. Proxy-Supported ........................................160
      18.39. Public .................................................161
      18.40. Range ..................................................162
      18.41. Referrer ...............................................164
      18.42. Request-Status .........................................164
      18.43. Require ................................................165
      18.44. Retry-After ............................................166
      18.45. RTP-Info ...............................................167
      18.46. Scale ..................................................169
      18.47. Seek-Style .............................................170
      18.48. Server .................................................171
      18.49. Session ................................................172
      18.50. Speed ..................................................173
      18.51. Supported ..............................................174
      18.52. Terminate-Reason .......................................175
      18.53. Timestamp ..............................................175
      18.54. Transport ..............................................176
      18.55. Unsupported ............................................183
      18.56. User-Agent .............................................184
      18.57. Via ....................................................184
      18.58. WWW-Authenticate .......................................185



Schulzrinne, et al.          Standards Track                    [Page 6]

RFC 7826                        RTSP 2.0                   December 2016


   19. Security Framework ...........................................185
      19.1. RTSP and HTTP Authentication ............................185
           19.1.1. Digest Authentication ............................186
      19.2. RTSP over TLS ...........................................187
      19.3. Security and Proxies ....................................188
           19.3.1. Accept-Credentials ...............................189
           19.3.2. User-Approved TLS Procedure ......................190
   20. Syntax .......................................................192
      20.1. Base Syntax .............................................193
      20.2. RTSP Protocol Definition ................................195
           20.2.1. Generic Protocol Elements ........................195
           20.2.2. Message Syntax ...................................198
           20.2.3. Header Syntax ....................................201
      20.3. SDP Extension Syntax ....................................209
   21. Security Considerations ......................................209
      21.1. Signaling Protocol Threats ..............................210
      21.2. Media Stream Delivery Threats ...........................213
           21.2.1. Remote DoS Attack ................................215
           21.2.2. RTP Security Analysis ............................216
   22. IANA Considerations ..........................................217
      22.1. Feature Tags ............................................218
           22.1.1. Description ......................................218
           22.1.2. Registering New Feature Tags with IANA ...........218
           22.1.3. Registered Entries ...............................219
      22.2. RTSP Methods ............................................219
           22.2.1. Description ......................................219
           22.2.2. Registering New Methods with IANA ................219
           22.2.3. Registered Entries ...............................220
      22.3. RTSP Status Codes .......................................220
           22.3.1. Description ......................................220
           22.3.2. Registering New Status Codes with IANA ...........220
           22.3.3. Registered Entries ...............................221
      22.4. RTSP Headers ............................................221
           22.4.1. Description ......................................221
           22.4.2. Registering New Headers with IANA ................221
           22.4.3. Registered Entries ...............................222
      22.5. Accept-Credentials ......................................223
           22.5.1. Accept-Credentials Policies ......................223
           22.5.2. Accept-Credentials Hash Algorithms ...............224
      22.6. Cache-Control Cache Directive Extensions ................224
      22.7. Media Properties ........................................225
           22.7.1. Description ......................................225
           22.7.2. Registration Rules ...............................226
           22.7.3. Registered Values ................................226
      22.8. Notify-Reason Values ....................................226
           22.8.1. Description ......................................226
           22.8.2. Registration Rules ...............................226
           22.8.3. Registered Values ................................227



Schulzrinne, et al.          Standards Track                    [Page 7]

RFC 7826                        RTSP 2.0                   December 2016


      22.9. Range Header Formats ....................................227
           22.9.1. Description ......................................227
           22.9.2. Registration Rules ...............................227
           22.9.3. Registered Values ................................228
      22.10. Terminate-Reason Header ................................228
           22.10.1. Redirect Reasons ................................228
           22.10.2. Terminate-Reason Header Parameters ..............229
      22.11. RTP-Info Header Parameters .............................229
           22.11.1. Description .....................................229
           22.11.2. Registration Rules ..............................229
           22.11.3. Registered Values ...............................230
      22.12. Seek-Style Policies ....................................230
           22.12.1. Description .....................................230
           22.12.2. Registration Rules ..............................230
           22.12.3. Registered Values ...............................230
      22.13. Transport Header Registries ............................231
           22.13.1. Transport Protocol Identifier ...................231
           22.13.2. Transport Modes .................................233
           22.13.3. Transport Parameters ............................233
      22.14. URI Schemes ............................................234
           22.14.1. The "rtsp" URI Scheme ...........................234
           22.14.2. The "rtsps" URI Scheme ..........................235
           22.14.3. The "rtspu" URI Scheme ..........................237
      22.15. SDP Attributes .........................................238
      22.16. Media Type Registration for text/parameters ............238
   23. References ...................................................240
      23.1. Normative References ....................................240
      23.2. Informative References ..................................245
   Appendix A. Examples .............................................248
      A.1. Media on Demand (Unicast) ................................248
      A.2. Media on Demand Using Pipelining .........................251
      A.3. Secured Media Session for On-Demand Content ..............254
      A.4. Media on Demand (Unicast) ................................257
      A.5. Single-Stream Container Files ............................260
      A.6. Live Media Presentation Using Multicast ..................263
      A.7. Capability Negotiation ...................................264
   Appendix B. RTSP Protocol State Machine ..........................265
      B.1. States ...................................................266
      B.2. State Variables ..........................................266
      B.3. Abbreviations ............................................266
      B.4. State Tables .............................................267
   Appendix C. Media-Transport Alternatives .........................272
      C.1. RTP ......................................................272
        C.1.1. AVP ..................................................272
        C.1.2. AVP/UDP ..............................................273
        C.1.3. AVPF/UDP .............................................274
        C.1.4. SAVP/UDP .............................................275
        C.1.5. SAVPF/UDP ............................................277



Schulzrinne, et al.          Standards Track                    [Page 8]

RFC 7826                        RTSP 2.0                   December 2016


        C.1.6. RTCP Usage with RTSP .................................278
      C.2. RTP over TCP .............................................279
        C.2.1. Interleaved RTP over TCP .............................280
        C.2.2. RTP over Independent TCP .............................280
      C.3. Handling Media-Clock Time Jumps in the RTP Media Layer ...284
      C.4. Handling RTP Timestamps after PAUSE ......................287
      C.5. RTSP/RTP Integration  ....................................290
      C.6. Scaling with RTP .........................................290
      C.7. Maintaining NPT Synchronization with RTP Timestamps ......290
      C.8. Continuous Audio .........................................290
      C.9. Multiple Sources in an RTP Session .......................290
      C.10. Usage of SSRCs and the RTCP BYE Message during an RTSP
            Session .................................................290
      C.11. Future Additions ........................................291
   Appendix D. Use of SDP for RTSP Session Descriptions .............292
      D.1. Definitions  .............................................292
        D.1.1. Control URI ..........................................292
        D.1.2. Media Streams ........................................294
        D.1.3. Payload Type(s) ......................................294
        D.1.4. Format-Specific Parameters ...........................294
        D.1.5. Directionality of Media Stream .......................295
        D.1.6. Range of Presentation ................................295
        D.1.7. Time of Availability .................................296
        D.1.8. Connection Information ...............................297
        D.1.9. Message Body Tag .....................................297
      D.2. Aggregate Control Not Available ..........................298
      D.3. Aggregate Control Available ..............................298
      D.4. Grouping of Media Lines in SDP ...........................299
      D.5. RTSP External SDP Delivery ...............................300
   Appendix E. RTSP Use Cases .......................................300
      E.1. On-Demand Playback of Stored Content .....................300
      E.2. Unicast Distribution of Live Content .....................302
      E.3. On-Demand Playback Using Multicast .......................303
      E.4. Inviting an RTSP Server into a Conference ................303
      E.5. Live Content Using Multicast .............................304
   Appendix F. Text Format for Parameters ...........................305
   Appendix G. Requirements for Unreliable Transport of RTSP ........305
   Appendix H. Backwards-Compatibility Considerations ...............306
      H.1. Play Request in Play State ...............................307
      H.2. Using Persistent Connections .............................307
   Appendix I. Changes ..............................................307
      I.1. Brief Overview ...........................................308
      I.2. Detailed List of Changes .................................309
   Acknowledgements .................................................316
   Contributors  ....................................................317
   Authors' Addresses ...............................................318





Schulzrinne, et al.          Standards Track                    [Page 9]

RFC 7826                        RTSP 2.0                   December 2016


1.  Introduction

   This memo defines version 2.0 of the Real-Time Streaming Protocol
   (RTSP 2.0).  RTSP 2.0 is an application-layer protocol for the setup
   and control over the delivery of data with real-time properties,
   typically streaming media.  Streaming media is, for instance, video
   on demand or audio live streaming.  Put simply, RTSP acts as a
   "network remote control" for multimedia servers.

   The protocol operates between RTSP 2.0 clients and servers, but it
   also supports the use of proxies placed between clients and servers.
   Clients can request information about streaming media from servers by
   asking for a description of the media or use media description
   provided externally.  The media delivery protocol is used to
   establish the media streams described by the media description.
   Clients can then request to play out the media, pause it, or stop it
   completely.  The requested media can consist of multiple audio and
   video streams that are delivered as time-synchronized streams from
   servers to clients.

   RTSP 2.0 is a replacement of RTSP 1.0 [RFC2326] and this document
   obsoletes that specification.  This protocol is based on RTSP 1.0 but
   is not backwards compatible other than in the basic version
   negotiation mechanism.  The changes between the two documents are
   listed in Appendix I.  There are many reasons why RTSP 2.0 can't be
   backwards compatible with RTSP 1.0; some of the main ones are as
   follows:

   o  Most headers that needed to be extensible did not define the
      allowed syntax, preventing safe deployment of extensions;

   o  the changed behavior of the PLAY method when received in Play
      state;

   o  the changed behavior of the extensibility model and its mechanism;
      and

   o  the change of syntax for some headers.

   There are so many small updates that changing versions became
   necessary to enable clarification and consistent behavior.  Anyone
   implementing RTSP for a new use case in which they have not installed
   RTSP 1.0 should only implement RTSP 2.0 to avoid having to deal with
   RTSP 1.0 inconsistencies.

   This document is structured as follows.  It begins with an overview
   of the protocol operations and its functions in an informal way.
   Then, a set of definitions of terms used and document conventions is



Schulzrinne, et al.          Standards Track                   [Page 10]

RFC 7826                        RTSP 2.0                   December 2016


   introduced.  These are followed by the actual RTSP 2.0 core protocol
   specification.  The appendices describe and define some
   functionalities that are not part of the core RTSP specification, but
   which are still important to enable some usages.  Among them, the RTP
   usage is defined in Appendix C, the Session Description Protocol
   (SDP) usage with RTSP is defined in Appendix D, and the "text/
   parameters" file format Appendix F, are three normative specification
   appendices.  Other appendices include a number of informational parts
   discussing the changes, use cases, different considerations or
   motivations.

2.  Protocol Overview

   This section provides an informative overview of the different
   mechanisms in the RTSP 2.0 protocol to give the reader a high-level
   understanding before getting into all the specific details.  In case
   of conflict with this description and the later sections, the later
   sections take precedence.  For more information about use cases
   considered for RTSP, see Appendix E.

   RTSP 2.0 is a bidirectional request and response protocol that first
   establishes a context including content resources (the media) and
   then controls the delivery of these content resources from the
   provider to the consumer.  RTSP has three fundamental parts: Session
   Establishment, Media Delivery Control, and an extensibility model
   described below.  The protocol is based on some assumptions about
   existing functionality to provide a complete solution for client-
   controlled real-time media delivery.

   RTSP uses text-based messages, requests and responses, that may
   contain a binary message body.  An RTSP request starts with a method
   line that identifies the method, the protocol, and version and the
   resource on which to act.  The resource is identified by a URI and
   the hostname part of the URI is used by RTSP client to resolve the
   IPv4 or IPv6 address of the RTSP server.  Following the method line
   are a number of RTSP headers.  These lines are ended by two
   consecutive carriage return line feed (CRLF) character pairs.  The
   message body, if present, follows the two CRLF character pairs, and
   the body's length is described by a message header.  RTSP responses
   are similar, but they start with a response line with the protocol
   and version followed by a status code and a reason phrase.  RTSP
   messages are sent over a reliable transport protocol between the
   client and server.  RTSP 2.0 requires clients and servers to
   implement TCP and TLS over TCP as mandatory transports for RTSP
   messages.






Schulzrinne, et al.          Standards Track                   [Page 11]

RFC 7826                        RTSP 2.0                   December 2016


2.1.  Presentation Description

   RTSP exists to provide access to multimedia presentations and content
   but tries to be agnostic about the media type or the actual media
   delivery protocol that is used.  To enable a client to implement a
   complete system, an RTSP-external mechanism for describing the
   presentation and the delivery protocol(s) is used.  RTSP assumes that
   this description is either delivered completely out of band or as a
   data object in the response to a client's request using the DESCRIBE
   method (Section 13.2).

   Parameters that commonly have to be included in the presentation
   description are the following:

   o  The number of media streams;

   o  the resource identifier for each media stream/resource that is to
      be controlled by RTSP;

   o  the protocol that will be used to deliver each media stream;

   o  the transport protocol parameters that are not negotiated or vary
      with each client;

   o  the media-encoding information enabling a client to correctly
      decode the media upon reception; and

   o  an aggregate control resource identifier.

   RTSP uses its own URI schemes ("rtsp" and "rtsps") to reference media
   resources and aggregates under common control (see Section 4.2).

   This specification describes in Appendix D how one uses SDP [RFC4566]
   for describing the presentation.

2.2.  Session Establishment

   The RTSP client can request the establishment of an RTSP session
   after having used the presentation description to determine which
   media streams are available, which media delivery protocol is used,
   and the resource identifiers of the media streams.  The RTSP session
   is a common context between the client and the server that consists
   of one or more media resources that are to be under common media
   delivery control.

   The client creates an RTSP session by sending a request using the
   SETUP method (Section 13.3) to the server.  In the Transport header
   (Section 18.54) of the SETUP request, the client also includes all



Schulzrinne, et al.          Standards Track                   [Page 12]

RFC 7826                        RTSP 2.0                   December 2016


   the transport parameters necessary to enable the media delivery
   protocol to function.  This includes parameters that are
   preestablished by the presentation description but necessary for any
   middlebox to correctly handle the media delivery protocols.  The
   Transport header in a request may contain multiple alternatives for
   media delivery in a prioritized list, which the server can select
   from.  These alternatives are typically based on information in the
   presentation description.

   When receiving a SETUP request, the server determines if the media
   resource is available and if one or more of the of the transport
   parameter specifications are acceptable.  If that is successful, an
   RTSP session context is created and the relevant parameters and state
   is stored.  An identifier is created for the RTSP session and
   included in the response in the Session header (Section 18.49).  The
   SETUP response includes a Transport header that specifies which of
   the alternatives has been selected and relevant parameters.

   A SETUP request that references an existing RTSP session but
   identifies a new media resource is a request to add that media
   resource under common control with the already-present media
   resources in an aggregated session.  A client can expect this to work
   for all media resources under RTSP control within a multimedia
   content container.  However, a server will likely refuse to aggregate
   resources from different content containers.  Even if an RTSP session
   contains only a single media stream, the RTSP session can be
   referenced by the aggregate control URI.

   To avoid an extra round trip in the session establishment of
   aggregated RTSP sessions, RTSP 2.0 supports pipelined requests; i.e.,
   the client can send multiple requests back-to-back without waiting
   first for the completion of any of them.  The client uses a client-
   selected identifier in the Pipelined-Requests header (Section 18.33)
   to instruct the server to bind multiple requests together as if they
   included the session identifier.

   The SETUP response also provides additional information about the
   established sessions in a couple of different headers.  The Media-
   Properties header (Section 18.29) includes a number of properties
   that apply for the aggregate that is valuable when doing media
   delivery control and configuring user interface.  The Accept-Ranges
   header (Section 18.5) informs the client about range formats that the
   server supports for these media resources.  The Media-Range header
   (Section 18.30) informs the client about the time range of the media
   currently available.






Schulzrinne, et al.          Standards Track                   [Page 13]

RFC 7826                        RTSP 2.0                   December 2016


2.3.  Media Delivery Control

   After having established an RTSP session, the client can start
   controlling the media delivery.  The basic operations are "begin
   playback", using the PLAY method (Section 13.4) and "suspend (pause)
   playback" by using the PAUSE method (Section 13.6).  PLAY also allows
   for choosing the starting media position from which the server should
   deliver the media.  The positioning is done by using the Range header
   (Section 18.40) that supports several different time formats: Normal
   Play Time (NPT) (Section 4.4.2), Society of Motion Picture and
   Television Engineers (SMPTE) Timestamps (Section 4.4.1), and absolute
   time (Section 4.4.3).  The Range header also allows the client to
   specify a position where delivery should end, thus allowing a
   specific interval to be delivered.

   The support for positioning/searching within media content depends on
   the content's media properties.  Content exists in a number of
   different types, such as on-demand, live, and live with simultaneous
   recording.  Even within these categories, there are differences in
   how the content is generated and distributed, which affect how it can
   be accessed for playback.  The properties applicable for the RTSP
   session are provided by the server in the SETUP response using the
   Media-Properties header (Section 18.29).  These are expressed using
   one or several independent attributes.  A first attribute is Random-
   Access, which indicates whether positioning is possible, and with
   what granularity.  Another aspect is whether the content will change
   during the lifetime of the session.  While on-demand content will be
   provided in full from the beginning, a live stream being recorded
   results in the length of the accessible content growing as the
   session goes on.  There also exists content that is dynamically built
   by a protocol other than RTSP and, thus, also changes in steps during
   the session, but maybe not continuously.  Furthermore, when content
   is recorded, there are cases where the complete content is not
   maintained, but, for example, only the last hour.  All of these
   properties result in the need for mechanisms that will be discussed
   below.

   When the client accesses on-demand content that allows random access,
   the client can issue the PLAY request for any point in the content
   between the start and the end.  The server will deliver media from
   the closest random access point prior to the requested point and
   indicate that in its PLAY response.  If the client issues a PAUSE,
   the delivery will be halted and the point at which the server stopped
   will be reported back in the response.  The client can later resume
   by sending a PLAY request without a Range header.  When the server is
   about to complete the PLAY request by delivering the end of the
   content or the requested range, the server will send a PLAY_NOTIFY
   request (Section 13.5) indicating this.



Schulzrinne, et al.          Standards Track                   [Page 14]

RFC 7826                        RTSP 2.0                   December 2016


   When playing live content with no extra functions, such as recording,
   the client will receive the live media from the server after having
   sent a PLAY request.  Seeking in such content is not possible as the
   server does not store it, but only forwards it from the source of the
   session.  Thus, delivery continues until the client sends a PAUSE
   request, tears down the session, or the content ends.

   For live sessions that are being recorded, the client will need to
   keep track of how the recording progresses.  Upon session
   establishment, the client will learn the current duration of the
   recording from the Media-Range header.  Because the recording is
   ongoing, the content grows in direct relation to the time passed.
   Therefore, each server's response to a PLAY request will contain the
   current Media-Range header.  The server should also regularly send
   (approximately every 5 minutes) the current media range in a
   PLAY_NOTIFY request (Section 13.5.2).  If the live transmission ends,
   the server must send a PLAY_NOTIFY request with the updated Media-
   Properties indicating that the content stopped being a recorded live
   session and instead became on-demand content; the request also
   contains the final media range.  While the live delivery continues,
   the client can request to play the current live point by using the
   NPT timescale symbol "now", or it can request a specific point in the
   available content by an explicit range request for that point.  If
   the requested point is outside of the available interval, the server
   will adjust the position to the closest available point, i.e., either
   at the beginning or the end.

   A special case of recording is that where the recording is not
   retained longer than a specific time period; thus, as the live
   delivery continues, the client can access any media within a moving
   window that covers, for example, "now" to "now" minus 1 hour.  A
   client that pauses on a specific point within the content may not be
   able to retrieve the content anymore.  If the client waits too long
   before resuming the pause point, the content may no longer be
   available.  In this case, the pause point will be adjusted to the
   closest point in the available media.

2.4.  Session Parameter Manipulations

   A session may have additional state or functionality that affects how
   the server or client treats the session or content, how it functions,
   or feedback on how well the session works.  Such extensions are not
   defined in this specification, but they may be covered in various
   extensions.  RTSP has two methods for retrieving and setting
   parameter values on either the client or the server: GET_PARAMETER
   (Section 13.8) and SET_PARAMETER (Section 13.9).  These methods carry
   the parameters in a message body of the appropriate format.  One can
   also use headers to query state with the GET_PARAMETER method.  As an



Schulzrinne, et al.          Standards Track                   [Page 15]

RFC 7826                        RTSP 2.0                   December 2016


   example, clients needing to know the current media range for a time-
   progressing session can use the GET_PARAMETER method and include the
   media range.  Furthermore, synchronization information can be
   requested by using a combination of RTP-Info (Section 18.45) and
   Range (Section 18.40).

   RTSP 2.0 does not have a strong mechanism for negotiating the headers
   or parameters and their formats.  However, responses will indicate
   request-headers or parameters that are not supported.  A priori
   determination of what features are available needs to be done through
   out-of-band mechanisms, like the session description, or through the
   usage of feature tags (Section 4.5).

2.5.  Media Delivery

   This document specifies how media is delivered with RTP [RFC3550]
   over UDP [RFC768], TCP [RFC793], or the RTSP connection.  Additional
   protocols may be specified in the future as needed.

   The usage of RTP as a media delivery protocol requires some
   additional information to function well.  The PLAY response contains
   information to enable reliable and timely delivery of how a client
   should synchronize different sources in the different RTP sessions.
   It also provides a mapping between RTP timestamps and the content-
   time scale.  When the server wants to notify the client about the
   completion of the media delivery, it sends a PLAY_NOTIFY request to
   the client.  The PLAY_NOTIFY request includes information about the
   stream end, including the last RTP sequence number for each stream,
   thus enabling the client to empty the buffer smoothly.

2.5.1.  Media Delivery Manipulations

   The basic playback functionality of RTSP enables delivery of a range
   of requested content to the client at the pace intended by the
   content's creator.  However, RTSP can also manipulate the delivery to
   the client in two ways.

   Scale:  The ratio of media-content time delivered per unit of
      playback time.

   Speed:  The ratio of playback time delivered per unit of wallclock
      time.

   Both affect the media delivery per time unit.  However, they
   manipulate two independent timescales and the effects are possible to
   combine.





Schulzrinne, et al.          Standards Track                   [Page 16]

RFC 7826                        RTSP 2.0                   December 2016


   Scale (Section 18.46) is used for fast-forward or slow-motion control
   as it changes the amount of content timescale that should be played
   back per time unit.  Scale > 1.0, means fast forward, e.g., scale =
   2.0 results in that 2 seconds of content being played back every
   second of playback.  Scale = 1.0 is the default value that is used if
   no scale is specified, i.e., playback at the content's original rate.
   Scale values between 0 and 1.0 provide for slow motion.  Scale can be
   negative to allow for reverse playback in either regular pace
   (scale = -1.0), fast backwards (scale < -1.0), or slow-motion
   backwards (-1.0 < scale < 0).  Scale = 0 would be equal to pause and
   is not allowed.

   In most cases, the realization of scale means server-side
   manipulation of the media to ensure that the client can actually play
   it back.  The nature of these media manipulations and when they are
   needed is highly media-type dependent.  Let's consider two common
   media types, audio and video.

   It is very difficult to modify the playback rate of audio.
   Typically, no more than a factor of two is possible while maintaining
   intelligibility by changing the pitch and rate of speech.  Music goes
   out of tune if one tries to manipulate the playback rate by
   resampling it.  This is a well-known problem, and audio is commonly
   muted or played back in short segments with skips to keep up with the
   current playback point.

   For video, it is possible to manipulate the frame rate, although the
   rendering capabilities are often limited to certain frame rates.
   Also, the allowed bitrates in decoding, the structure used in the
   encoding, and the dependency between frames and other capabilities of
   the rendering device limits the possible manipulations.  Therefore,
   the basic fast-forward capabilities often are implemented by
   selecting certain subsets of frames.

   Due to the media restrictions, the possible scale values are commonly
   restricted to the set of realizable scale ratios.  To enable the
   clients to select from the possible scale values, RTSP can signal the
   supported scale ratios for the content.  To support aggregated or
   dynamic content, where this may change during the ongoing session and
   dependent on the location within the content, a mechanism for
   updating the media properties and the scale factor currently in use,
   exists.

   Speed (Section 18.50) affects how much of the playback timeline is
   delivered in a given wallclock period.  The default is Speed = 1
   which means to deliver at the same rate the media is consumed.
   Speed > 1 means that the receiver will get content faster than it
   regularly would consume it.  Speed < 1 means that delivery is slower



Schulzrinne, et al.          Standards Track                   [Page 17]

RFC 7826                        RTSP 2.0                   December 2016


   than the regular media rate.  Speed values of 0 or lower have no
   meaning and are not allowed.  This mechanism enables two general
   functionalities.  One is client-side scale operations, i.e., the
   client receives all the frames and makes the adjustment to the
   playback locally.  The second is delivery control for the buffering
   of media.  By specifying a speed over 1.0, the client can build up
   the amount of playback time it has present in its buffers to a level
   that is sufficient for its needs.

   A naive implementation of Speed would only affect the transmission
   schedule of the media and has a clear impact on the needed bandwidth.
   This would result in the data rate being proportional to the speed
   factor.  Speed = 1.5, i.e., 50% faster than normal delivery, would
   result in a 50% increase in the data-transport rate.  Whether or not
   that can be supported depends solely on the underlying network path.
   Scale may also have some impact on the required bandwidth due to the
   manipulation of the content in the new playback schedule.  An example
   is fast forward where only the independently decodable intra-frames
   are included in the media stream.  This usage of solely intra-frames
   increases the data rate significantly compared to a normal sequence
   with the same number of frames, where most frames are encoded using
   prediction.

   This potential increase of the data rate needs to be handled by the
   media sender.  The client has requested that the media be delivered
   in a specific way, which should be honored.  However, the media
   sender cannot ignore if the network path between the sender and the
   receiver can't handle the resulting media stream.  In that case, the
   media stream needs to be adapted to fit the available resources of
   the path.  This can result in a reduced media quality.

   The need for bitrate adaptation becomes especially problematic in
   connection with the Speed semantics.  If the goal is to fill up the
   buffer, the client may not want to do that at the cost of reduced
   quality.  If the client wants to make local playout changes, then it
   may actually require that the requested speed be honored.  To resolve
   this issue, Speed uses a range so that both cases can be supported.
   The server is requested to use the highest possible speed value
   within the range, which is compatible with the available bandwidth.
   As long as the server can maintain a speed value within the range, it
   shall not change the media quality, but instead modify the actual
   delivery rate in response to available bandwidth and reflect this in
   the Speed value in the response.  However, if this is not possible,
   the server should instead modify the media quality to respect the
   lowest speed value and the available bandwidth.






Schulzrinne, et al.          Standards Track                   [Page 18]

RFC 7826                        RTSP 2.0                   December 2016


   This functionality enables the local scaling implementation to use a
   tight range, or even a range where the lower bound equals the upper
   bound, to identify that it requires the server to deliver the
   requested amount of media time per delivery time, independent of how
   much it needs to adapt the media quality to fit within the available
   path bandwidth.  For buffer filling, it is suitable to use a range
   with a reasonable span and with a lower bound at the nominal media
   rate 1.0, such as 1.0 - 2.5.  If the client wants to reduce the
   buffer, it can specify an upper bound that is below 1.0 to force the
   server to deliver slower than the nominal media rate.

2.6.  Session Maintenance and Termination

   The session context that has been established is kept alive by having
   the client show liveness.  This is done in two main ways:

   o  Media-transport protocol keep-alive.  RTP Control Protocol (RTCP)
      may be used when using RTP.

   o  Any RTSP request referencing the session context.

   Section 10.5 discusses the methods for showing liveness in more
   depth.  If the client fails to show liveness for more than the
   established session timeout value (normally 60 seconds), the server
   may terminate the context.  Other values may be selected by the
   server through the inclusion of the timeout parameter in the session
   header.

   The session context is normally terminated by the client sending a
   TEARDOWN request (Section 13.7) to the server referencing the
   aggregated control URI.  An individual media resource can be removed
   from a session context by a TEARDOWN request referencing that
   particular media resource.  If all media resources are removed from a
   session context, the session context is terminated.

   A client may keep the session alive indefinitely if allowed by the
   server; however, a client is advised to release the session context
   when an extended period of time without media delivery activity has
   passed.  The client can re-establish the session context if required
   later.  What constitutes an extended period of time is dependent on
   the client, server, and their usage.  It is recommended that the
   client terminate the session before ten times the session timeout
   value has passed.  A server may terminate the session after one
   session timeout period without any client activity beyond keep-alive.
   When a server terminates the session context, it does so by sending a
   TEARDOWN request indicating the reason.





Schulzrinne, et al.          Standards Track                   [Page 19]

RFC 7826                        RTSP 2.0                   December 2016


   A server can also request that the client tear down the session and
   re-establish it at an alternative server, as may be needed for
   maintenance.  This is done by using the REDIRECT method
   (Section 13.10).  The Terminate-Reason header (Section 18.52) is used
   to indicate when and why.  The Location header indicates where it
   should connect if there is an alternative server available.  When the
   deadline expires, the server simply stops providing the service.  To
   achieve a clean closure, the client needs to initiate session
   termination prior to the deadline.  In case the server has no other
   server to redirect to, and it wants to close the session for
   maintenance, it shall use the TEARDOWN method with a Terminate-Reason
   header.

2.7.  Extending RTSP

   RTSP is quite a versatile protocol that supports extensions in many
   different directions.  Even this core specification contains several
   blocks of functionality that are optional to implement.  The use case
   and need for the protocol deployment should determine what parts are
   implemented.  Allowing for extensions makes it possible for RTSP to
   address additional use cases.  However, extensions will affect the
   interoperability of the protocol; therefore, it is important that
   they can be added in a structured way.

   The client can learn the capability of a server by using the OPTIONS
   method (Section 13.1) and the Supported header (Section 18.51).  It
   can also try and possibly fail using new methods or require that
   particular features be supported using the Require (Section 18.43) or
   Proxy-Require (Section 18.37) header.

   The RTSP, in itself, can be extended in three ways, listed here in
   increasing order of the magnitude of changes supported:

   o  Existing methods can be extended with new parameters, for example,
      headers, as long as these parameters can be safely ignored by the
      recipient.  If the client needs negative acknowledgment when a
      method extension is not supported, a tag corresponding to the
      extension may be added in the field of the Require or Proxy-
      Require headers.

   o  New methods can be added.  If the recipient of the message does
      not understand the request, it must respond with error code 501
      (Not Implemented) so that the sender can avoid using this method
      again.  A client may also use the OPTIONS method to inquire about
      methods supported by the server.  The server must list the methods
      it supports using the Public response-header.





Schulzrinne, et al.          Standards Track                   [Page 20]

RFC 7826                        RTSP 2.0                   December 2016


   o  A new version of the protocol can be defined, allowing almost all
      aspects (except the position of the protocol version number) to
      change.  A new version of the protocol must be registered through
      a Standards Track document.

   The basic capability discovery mechanism can be used to both discover
   support for a certain feature and to ensure that a feature is
   available when performing a request.  For a detailed explanation of
   this, see Section 11.

   New media delivery protocols may be added and negotiated at session
   establishment, in addition to extensions to the core protocol.
   Certain types of protocol manipulations can be done through parameter
   formats using SET_PARAMETER and GET_PARAMETER.

3.  Document Conventions

3.1.  Notational Conventions

   All the mechanisms specified in this document are described in both
   prose and the Augmented Backus-Naur form (ABNF) described in detail
   in [RFC5234].

   Indented paragraphs are used to provide informative background and
   motivation.  This is intended to give readers who were not involved
   with the formulation of the specification an understanding of why
   things are the way they are in RTSP.

   The key words "MUST", "MUST NOT", "REQUIRED", "SHALL", "SHALL NOT",
   "SHOULD", "SHOULD NOT", "RECOMMENDED", "NOT RECOMMENDED", "MAY", and
   "OPTIONAL" in this document are to be interpreted as described in
   [RFC2119].

   The word, "unspecified" is used to indicate functionality or features
   that are not defined in this specification.  Such functionality
   cannot be used in a standardized manner without further definition in
   an extension specification to RTSP.

3.2.  Terminology

   Aggregate control:  The concept of controlling multiple streams using
      a single timeline, generally one maintained by the server.  A
      client, for example, uses aggregate control when it issues a
      single play or pause message to simultaneously control both the
      audio and video in a movie.  A session that is under aggregate
      control is referred to as an "aggregated session".





Schulzrinne, et al.          Standards Track                   [Page 21]

RFC 7826                        RTSP 2.0                   December 2016


   Aggregate control URI:  The URI used in an RTSP request to refer to
      and control an aggregated session.  It normally, but not always,
      corresponds to the presentation URI specified in the session
      description.  See Section 13.3 for more information.

   Client:  The client is the requester of media service from the media
      server.

   Connection:  A transport-layer virtual circuit established between
      two programs for the purpose of communication.

   Container file:  A file that may contain multiple media streams that
      often constitute a presentation when played together.  The concept
      of a container file is not embedded in the protocol.  However,
      RTSP servers may offer aggregate control on the media streams
      within these files.

   Continuous media:  Data where there is a timing relationship between
      source and sink; that is, the sink needs to reproduce the timing
      relationship that existed at the source.  The most common examples
      of continuous media are audio and motion video.  Continuous media
      can be real time (interactive or conversational), where there is a
      "tight" timing relationship between source and sink or it can be
      streaming where the relationship is less strict.

   Feature tag:  A tag representing a certain set of functionality,
      i.e., a feature.

   IRI:  An Internationalized Resource Identifier is similar to a URI
      but allows characters from the whole Universal Character Set
      (Unicode/ISO 10646), rather than the US-ASCII only.  See [RFC3987]
      for more information.

   Live:  A live presentation or session originates media from an event
      taking place at the same time as the media delivery.  Live
      sessions often have an unbound or only loosely defined duration
      and seek operations may not be possible.

   Media initialization:  The datatype- or codec-specific
      initialization.  This includes such things as clock rates, color
      tables, etc.  Any transport-independent information that is
      required by a client for playback of a media stream occurs in the
      media initialization phase of stream setup.

   Media parameter:  A parameter specific to a media type that may be
      changed before or during stream delivery.





Schulzrinne, et al.          Standards Track                   [Page 22]

RFC 7826                        RTSP 2.0                   December 2016


   Media server:  The server providing media-delivery services for one
      or more media streams.  Different media streams within a
      presentation may originate from different media servers.  A media
      server may reside on the same host or on a different host from
      which the presentation is invoked.

   (Media) Stream:  A single media instance, e.g., an audio stream or a
      video stream as well as a single whiteboard or shared application
      group.  When using RTP, a stream consists of all RTP and RTCP
      packets created by a media source within an RTP session.

   Message:  The basic unit of RTSP communication, consisting of a
      structured sequence of octets matching the syntax defined in
      Section 20 and transmitted over a transport between RTSP agents.
      A message is either a request or a response.

   Message body:  The information transferred as the payload of a
      message (request or response).  A message body consists of meta-
      information in the form of message body headers and content in the
      form of an arbitrary number of data octets, as described in
      Section 9.

   Non-aggregated control:  Control of a single media stream.

   Presentation:  A set of one or more streams presented to the client
      as a complete media feed and described by a presentation
      description as defined below.  Presentations with more than one
      media stream are often handled in RTSP under aggregate control.

   Presentation description:  A presentation description contains
      information about one or more media streams within a presentation,
      such as the set of encodings, network addresses, and information
      about the content.  Other IETF protocols, such as SDP ([RFC4566]),
      use the term "session" for a presentation.  The presentation
      description may take several different formats, including but not
      limited to SDP format.

   Response:  An RTSP response to a request.  One type of RTSP message.
      If an HTTP response is meant, it is indicated explicitly.

   Request:  An RTSP request.  One type of RTSP message.  If an HTTP
      request is meant, it is indicated explicitly.

   Request-URI:  The URI used in a request to indicate the resource on
      which the request is to be performed.






Schulzrinne, et al.          Standards Track                   [Page 23]

RFC 7826                        RTSP 2.0                   December 2016


   RTSP agent:  Either an RTSP client, an RTSP server, or an RTSP proxy.
      In this specification, there are many capabilities that are common
      to these three entities such as the capability to send requests or
      receive responses.  This term will be used when describing
      functionality that is applicable to all three of these entities.

   RTSP session:  A stateful abstraction upon which the main control
      methods of RTSP operate.  An RTSP session is a common context; it
      is created and maintained on a client's request and can be
      destroyed by either the client or server.  It is established by an
      RTSP server upon the completion of a successful SETUP request
      (when a 200 OK response is sent) and is labeled with a session
      identifier at that time.  The session exists until timed out by
      the server or explicitly removed by a TEARDOWN request.  An RTSP
      session is a stateful entity; an RTSP server maintains an explicit
      session state machine (see Appendix B) where most state
      transitions are triggered by client requests.  The existence of a
      session implies the existence of state about the session's media
      streams and their respective transport mechanisms.  A given
      session can have one or more media streams associated with it.  An
      RTSP server uses the session to aggregate control over multiple
      media streams.

   Origin server:  The server on which a given resource resides.

   Seeking:  Requesting playback from a particular point in the content
      time line.

   Transport initialization:  The negotiation of transport information
      (e.g., port numbers, transport protocols) between the client and
      the server.

   URI:  A Universal Resource Identifier; see [RFC3986].  The URIs used
      in RTSP are generally URLs as they give a location for the
      resource.  As URLs are a subset of URIs, they will be referred to
      as URIs to cover also the cases when an RTSP URI would not be a
      URL.

   URL:  A Universal Resource Locator is a URI that identifies the
      resource through its primary access mechanism rather than
      identifying the resource by name or by some other attribute(s) of
      that resource.









Schulzrinne, et al.          Standards Track                   [Page 24]

RFC 7826                        RTSP 2.0                   December 2016


4.  Protocol Parameters

4.1.  RTSP Version

   This specification defines version 2.0 of RTSP.

   RTSP uses a "<major>.<minor>" numbering scheme to indicate versions
   of the protocol.  The protocol versioning policy is intended to allow
   the sender to indicate the format of a message and its capacity for
   understanding further RTSP communication rather than the features
   obtained via that communication.  No change is made to the version
   number for the addition of message components that do not affect
   communication behavior or that only add to extensible field values.

   The <minor> number is incremented when the changes made to the
   protocol add features that do not change the general message parsing
   algorithm but that may add to the message semantics and imply
   additional capabilities of the sender.  The <major> number is
   incremented when the format of a message within the protocol is
   changed.  The version of an RTSP message is indicated by an RTSP-
   Version field in the first line of the message.  Note that the major
   and minor numbers MUST be treated as separate integers and that each
   MAY be incremented higher than a single digit.  Thus, RTSP/2.4 is a
   lower version than RTSP/2.13, which, in turn, is lower than
   RTSP/12.3.  Leading zeros SHALL NOT be sent and MUST be ignored by
   recipients.

4.2.  RTSP IRI and URI

   RTSP 2.0 defines and registers or updates three URI schemes "rtsp",
   "rtsps", and "rtspu".  The usage of the last, "rtspu", is unspecified
   in RTSP 2.0 and is defined here to register the URI scheme that was
   defined in RTSP 1.0.  The "rtspu" scheme indicates unspecified
   transport of the RTSP messages over unreliable transport means (UDP
   in RTSP 1.0).  An RTSP server MUST respond with an error code
   indicating the "rtspu" scheme is not implemented (501) to a request
   that carries a "rtspu" URI scheme.

   The details of the syntax of "rtsp" and "rtsps" URIs have been
   changed from RTSP 1.0.  These changes include the addition of:

   o  Support for an IPv6 literal in the host part and future IP
      literals through a mechanism defined in [RFC3986].

   o  A new relative format to use in the RTSP elements that is not
      required to start with "/".





Schulzrinne, et al.          Standards Track                   [Page 25]

RFC 7826                        RTSP 2.0                   December 2016


   Neither should have any significant impact on interoperability.  If
   IPv6 literals are needed in the RTSP URI, then that RTSP server must
   be IPv6 capable, and RTSP 1.0 is not a fully IPv6 capable protocol.
   If an RTSP 1.0 client attempts to process the URI, the URI will not
   match the allowed syntax, it will be considered invalid, and
   processing will be stopped.  This is clearly a failure to reach the
   resource; however, it is not a signification issue as RTSP 2.0
   support was needed anyway in both server and client.  Thus, failure
   will only occur in a later step when there is an RTSP version
   mismatch between client and server.  The second change will only
   occur inside RTSP message headers, as the Request-URI must be an
   absolute URI.  Thus, such usages will only occur after an agent has
   accepted and started processing RTSP 2.0 messages, and an agent using
   RTSP 1.0 only will not be required to parse such types of relative
   URIs.

   This specification also defines the format of RTSP IRIs [RFC3987]
   that can be used as RTSP resource identifiers and locators on web
   pages, user interfaces, on paper, etc.  However, the RTSP request
   message format only allows usage of the absolute URI format.  The
   RTSP IRI format MUST use the rules and transformation for IRIs to
   URIs, as defined in [RFC3987].  This allows a URI that matches the
   RTSP 2.0 specification, and so is suitable for use in a request, to
   be created from an RTSP IRI.

   The RTSP IRI and URI are both syntax restricted compared to the
   generic syntax defined in [RFC3986] and [RFC3987]:

   o  An absolute URI requires the authority part; i.e., a host identity
      MUST be provided.

   o  Parameters in the path element are prefixed with the reserved
      separator ";".

   The "scheme" and "host" parts of all URIs [RFC3986] and IRIs
   [RFC3987] are case insensitive.  All other parts of RTSP URIs and
   IRIs are case sensitive, and they MUST NOT be case mapped.

   The fragment identifier is used as defined in Sections 3.5 and 4.3 of
   [RFC3986], i.e., the fragment is to be stripped from the IRI by the
   requester and not included in the Request-URI.  The user agent needs
   to interpret the value of the fragment based on the media type the
   request relates to; i.e., the media type indicated in Content-Type
   header in the response to a DESCRIBE request.

   The syntax of any URI query string is unspecified and responder
   (usually the server) specific.  The query is, from the requester's
   perspective, an opaque string and needs to be handled as such.



Schulzrinne, et al.          Standards Track                   [Page 26]

RFC 7826                        RTSP 2.0                   December 2016


   Please note that relative URIs with queries are difficult to handle
   due to the relative URI handling rules of RFC 3986.  Any change of
   the path element using a relative URI results in the stripping of the
   query, which means the relative part needs to contain the query.

   The URI scheme "rtsp" requires that commands be issued via a reliable
   protocol (within the Internet, TCP), while the scheme "rtsps"
   identifies a reliable transport using secure transport (TLS
   [RFC5246]); see Section 19.

   For the scheme "rtsp", if no port number is provided in the authority
   part of the URI, the port number 554 MUST be used.  For the scheme
   "rtsps", if no port number is provided in the authority part of the
   URI port number, the TCP port 322 MUST be used.

   A presentation or a stream is identified by a textual media
   identifier, using the character set and escape conventions of URIs
   [RFC3986].  URIs may refer to a stream or an aggregate of streams;
   i.e., a presentation.  Accordingly, requests described in Section 13
   can apply to either the whole presentation or an individual stream
   within the presentation.  Note that some request methods can only be
   applied to streams, not presentations, and vice versa.

   For example, the RTSP URI:

      rtsp://media.example.com:554/twister/audiotrack

   may identify the audio stream within the presentation "twister",
   which can be controlled via RTSP requests issued over a TCP
   connection to port 554 of host media.example.com.

   Also, the RTSP URI:

      rtsp://media.example.com:554/twister

   identifies the presentation "twister", which may be composed of audio
   and video streams, but could also be something else, such as a random
   media redirector.

      This does not imply a standard way to reference streams in URIs.
      The presentation description defines the hierarchical
      relationships in the presentation and the URIs for the individual
      streams.  A presentation description may name a stream "a.mov" and
      the whole presentation "b.mov".

   The path components of the RTSP URI are opaque to the client and do
   not imply any particular file system structure for the server.




Schulzrinne, et al.          Standards Track                   [Page 27]

RFC 7826                        RTSP 2.0                   December 2016


      This decoupling also allows presentation descriptions to be used
      with non-RTSP media control protocols simply by replacing the
      scheme in the URI.

4.3.  Session Identifiers

   Session identifiers are strings of a length between 8-128 characters.
   A session identifier MUST be generated using methods that make it
   cryptographically random (see [RFC4086]).  It is RECOMMENDED that a
   session identifier contain 128 bits of entropy, i.e., approximately
   22 characters from a high-quality generator (see Section 21).
   However, note that the session identifier does not provide any
   security against session hijacking unless it is kept confidential by
   the client, server, and trusted proxies.

4.4.  Media-Time Formats

   RTSP currently supports three different media-time formats defined
   below.  Additional time formats may be specified in the future.
   These time formats can be used with the Range header (Section 18.40)
   to request playback and specify at which media position protocol
   requests actually will or have taken place.  They are also used in
   description of the media's properties using the Media-Range header
   (Section 18.30).  The unqualified format identifier is used on its
   own in Accept-Ranges header (Section 18.5) to declare supported time
   formats and also in the Range header (Section 18.40) to request the
   time format used in the response.

4.4.1.  SMPTE-Relative Timestamps

   A timestamp may use a format derived from a Society of Motion Picture
   and Television Engineers (SMPTE) specification and expresses time
   offsets anchored at the start of the media clip.  Relative timestamps
   are expressed as SMPTE time codes [SMPTE-TC] for frame-level access
   accuracy.  The time code has the format:

      hours:minutes:seconds:frames.subframes

   with the origin at the start of the clip.  The default SMPTE format
   is "SMPTE 30 drop" format, with a frame rate of 29.97 frames per
   second.  Other SMPTE codes MAY be supported (such as "SMPTE 25")
   through the use of "smpte-type".  For SMPTE 30, the "frames" field in
   the time value can assume the values 0 through 29.  The difference
   between 30 and 29.97 frames per second is handled by dropping the
   first two frame indices (values 00 and 01) of every minute, except
   every tenth minute.  If the frame and the subframe values are zero,
   they may be omitted.  Subframes are measured in hundredths of a
   frame.



Schulzrinne, et al.          Standards Track                   [Page 28]

RFC 7826                        RTSP 2.0                   December 2016


   Examples:

     smpte=10:12:33:20-
     smpte=10:07:33-
     smpte=10:07:00-10:07:33:05.01
     smpte-25=10:07:00-10:07:33:05.01

4.4.2.  Normal Play Time

   Normal Play Time (NPT) indicates the stream-absolute position
   relative to the beginning of the presentation.  The timestamp
   consists of two parts: The mandatory first part may be expressed in
   either seconds only or in hours, minutes, and seconds.  The optional
   second part consists of a decimal point and decimal figures and
   indicates fractions of a second.

   The beginning of a presentation corresponds to 0.0 seconds.  Negative
   values are not defined.

   The special constant "now" is defined as the current instant of a
   live event.  It MAY only be used for live events and MUST NOT be used
   for on-demand (i.e., non-live) content.

   NPT is defined as in Digital Storage Media Command and Control
   (DSMb;CC) [ISO.13818-6.1995]:

      Intuitively, NPT is the clock the viewer associates with a
      program.  It is often digitally displayed on a DVD player.  NPT
      advances normally when in normal play mode (scale = 1), advances
      at a faster rate when in fast-scan forward (high positive scale
      ratio), decrements when in scan reverse (negative scale ratio) and
      is fixed in pause mode.  NPT is (logically) equivalent to SMPTE
      time codes.

   Examples:

     npt=123.45-125
     npt=12:05:35.3-
     npt=now-












Schulzrinne, et al.          Standards Track                   [Page 29]

RFC 7826                        RTSP 2.0                   December 2016


   The syntax is based on ISO 8601 [ISO.8601.2000] and expresses the
   time elapsed since presentation start, with two different notations
   allowed:

   o  The npt-hhmmss notation uses an ISO 8601 extended complete
      representation of the time of the day format (Section 5.3.1.1 of
      [ISO.8601.2000] ) using colons (":") as separators between hours,
      minutes, and seconds (hh:mm:ss).  The hour counter is not limited
      to 0-24 hours; up to nineteen (19) hour digits are allowed.

      *  In accordance with the requirements of the ISO 8601 time
         format, the hours, minutes, and seconds MUST all be present,
         with two digits used for minutes and for seconds and with at
         least two digits for hours.  An NPT of 7 minutes and 0 seconds
         is represented as "00:07:00", and an NPT of 392 hours, 0
         minutes, and 6 seconds is represented as "392:00:06".

      *  RTSP 1.0 allowed NPT in the npt-hhmmss notation without any
         leading zeros to ensure that implementations don't fail; for
         backward compatibility, all RTSP 2.0 implementations are
         REQUIRED to support receiving NPT values, hours, minutes, or
         seconds, without leading zeros.

   o  The npt-sec notation expresses the time in seconds, using between
      one and nineteen (19) digits.

   Both notations allow decimal fractions of seconds as specified in
   Section 5.3.1.3 of [ISO.8601.2000], using at most nine digits, and
   allowing only "." (full stop) as the decimal separator.

   The npt-sec notation is optimized for automatic generation; the npt-
   hhmmss notation is optimized for consumption by human readers.  The
   "now" constant allows clients to request to receive the live feed
   rather than the stored or time-delayed version.  This is needed since
   neither absolute time nor zero time are appropriate for this case.

4.4.3.  Absolute Time

   Absolute time is expressed using a timestamp based on ISO 8601
   [ISO.8601.2000].  The date is a complete representation of the
   calendar date in basic format (YYYYMMDD) without separators (per
   Section 5.2.1.1 of [ISO.8601.2000]).  The time of day is provided in
   the complete representation basic format (hhmmss) as specified in
   Section 5.3.1.1 of [ISO.8601.2000], allowing decimal fractions of
   seconds following Section 5.3.1.3 requiring "." (full stop) as
   decimal separator and limiting the number of digits to no more than
   nine.  The time expressed MUST use UTC (GMT), i.e., no time zone
   offsets are allowed.  The full date and time specification is the



Schulzrinne, et al.          Standards Track                   [Page 30]

RFC 7826                        RTSP 2.0                   December 2016


   eight-digit date followed by a "T" followed by the six-digit time
   value, optionally followed by a full stop followed by one to nine
   fractions of a second and ended by "Z", e.g., YYYYMMDDThhmmss.ssZ.

      The reasons for this time format rather than using "Date and Time
      on the Internet: Timestamps" [RFC3339] are historic.  We continue
      to use the format specified in RTSP 1.0.  The motivations raised
      in RFC 3339 apply to why a selection from ISO 8601 was made;
      however, a different and even more restrictive selection was
      applied in this case.

   Below are three examples of media time formats, first, a request for
   a clock format range request for a starting time of November 8, 1996
   at 14 h 37 min and 20 1/4 seconds UTC playing for 10 min and 5
   seconds, followed by a Media-Properties header's "Time-Limited" UTC
   property for the 24th of December 2014 at 15 hours and 00 minutes,
   and finally a Terminate-Reason header "time" property for the 18th of
   June 2013 at 16 hours, 12 minutes, and 56 seconds:

     clock=19961108T143720.25Z-19961108T144725.25Z
     Time-Limited=20141224T1500Z
     time=20130618T161256Z

4.5.  Feature Tags

   Feature tags are unique identifiers used to designate features in
   RTSP.  These tags are used in Require (Section 18.43), Proxy-Require
   (Section 18.37), Proxy-Supported (Section 18.38), Supported
   (Section 18.51), and Unsupported (Section 18.55) header fields.

   A feature tag definition MUST indicate which combination of clients,
   servers, or proxies to which it applies.

   The creator of a new RTSP feature tag should either prefix the
   feature tag with a reverse domain name (e.g.,
   "com.example.mynewfeature" is an apt name for a feature whose
   inventor can be reached at "example.com") or register the new feature
   tag with the Internet Assigned N