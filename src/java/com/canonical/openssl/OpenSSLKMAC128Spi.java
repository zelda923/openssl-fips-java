class OpenSSLKMAC128Spi extends OpenSSLMACSpi {
    protected String getAlgorithm() {
        return "KMAC-128";
    }

    protected String getCipherType() {
        return null;
    }

    protected String getDigestType() {
        return null;
    }

    protected byte[] getIV() {
        return null; 
    }
}

