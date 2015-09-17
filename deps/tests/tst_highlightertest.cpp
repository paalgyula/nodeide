#include <QString>
#include <QtTest>

class HighlighterTest : public QObject
{
    Q_OBJECT

public:
    HighlighterTest();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void testCase1();
};

HighlighterTest::HighlighterTest()
{
}

void HighlighterTest::initTestCase()
{
}

void HighlighterTest::cleanupTestCase()
{
}

void HighlighterTest::testCase1()
{
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(HighlighterTest)

#include "tst_highlightertest.moc"
