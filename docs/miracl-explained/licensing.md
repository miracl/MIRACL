* [What Is Miracl](README.md)
* [Security Advisory](security-advisory.md)
* [Benchmarks](benchmarks.md)
* [Miracl Standard Curves](miracl-standard-curves.md)
* [IEEE 1363](ieee-1363.md)
* [Elliptic Curves](elliptic-curves.md)
* Licensing
* Reference Manual
	* [Low Level Routines](reference-manual/low-level-routines.md)
	* [Advanced Arithmetic Routines](reference-manual/advanced-arithmetic-routines.md)
	* [Montgomery Arithmetic Routines](reference-manual/montgomery-arithmetic-routines.md)
	* [ZZn2 Arithmetic Routines](reference-manual/zzn2-arithmetic-routines.md)
	* [Encryption Routines](reference-manual/encryption-routines.md)
	* [Elliptic Curve Routines](reference-manual/elliptic-curve-routines.md)
	* [Floating Slash Routines](reference-manual/floating-slash-routines.md)
	* [Structure Reference](reference-manual/structure-reference.md)


Licensing
---

MIRACL has been under continuous development since 1988. It is currently licensed to hundreds of leading companies in the United States, Brazil, Britain, Germany, France, Switzerland, South Africa and Australia. Its cryptographic runtimes can be found in chips, operating systems and software applications in industries ranging from defense and intelligence to financial services and software as a service companies.

## What's the license for MIRACL?

MIRACL licenses are offered according to a dual licensing scheme. The FOSS license applicable to cryptographic implementations is the Affero GPL (AGPL) License, version 3. MIRACL is offered as a standard commercial license with any subscription to the CertiVox Key Management Service. Companies that are not comfortable with AGPL and are using MIRACL without a subscription to the CertiVox Key Management Service can acquire a commercial license for use of the software from by contacting <sales@miracl.com>.

## Why is AGPL sometimes incompatible with commercial software?

From a purely theoretical viewpoint, there is no incompatibility between AGPL and commercial applications. One may be running a commercial service while making the source code open and available to third-parties. Of course, things are likely different in practice. AGPL employs so-called 'strong copyleft' – for example: the demand that all the software linked against free software (free in GNU/FSF sense) is also free software and freely available. GNU Public License is the most famous of such 'strong copyleft' FOSS licenses. The GPL copyleft clause triggers when an application is distributed outside of company boundaries. The GPL license was created at a time when the web did not exist, let alone the possibility to use applications remotely through a web browser. Because of this, companies could deploy GPL code commercially on a web server without betraying the letter, but arguably betraying the spirit of the GPL. This is called the ASP loophole. This is the context in which Affero was designed. The basic idea is that making AGPL software available through a web server constitutes distribution, and this is enough to trigger the strong copyleft provisions that many are already familiar with because of GPL. In other words, all of the software that links to the AGPL library must also be released with a compatible Free or Open-Source license. Commercial companies or applications developed that are deployed in the financial services, national defense or intelligence industries are unlikely to want to have to disclose and distribute the source code with which they use MIRACL. If that is the case, closed source licenses are available that do not require the company, application or organization to disclose the source code with which it uses MIRACL. This is called selling/buying a GPL exception in GNU parlance (others simply call this 'dual licensing').

## If I use the AGPL license, will I need to open-source my code?

Yes, you will. Exactly like regular GPL, linking your code to GPL code creates derivative work (in the copyright sense of the term) and this is enough to trigger the 'copyleft' provisions. FSF is adamant on this interpretation and so is CertiVox.
Q: What's the price of a commercial license and / or support from CertiVox?

CertiVox issues a commercial license for MIRACL when a subscription to the CertiVox Key Management Service is issued. Additionally, CertiVox will offer enhanced developer support for MIRACL, which will optionally include cryptographic design consulting. CertiVox will publish publicly available pricing for both in the next few weeks. If you need a commercial license and / or support immediately, please contact <sales@miracl.com>.
