node("Linux") {
  stage('SCM') {
    checkout scm
  }
  stage('Download Build Wrapper') {
    sh "mkdir -p .sonar"
    sh "curl -sSLo build-wrapper-linux-x86.zip https://sonarqube.hurrhnn.xyz/static/cpp/build-wrapper-linux-x86.zip"
    sh "unzip -o build-wrapper-linux-x86.zip -d .sonar"
  }
  stage('Build') {
    sh "cmake -DCMAKE_BUILD_TYPE=Debug -DBUFEP_TEST_ALERM=ON -B build/ ."
    sh ".sonar/build-wrapper-linux-x86/build-wrapper-linux-x86-64 --out-dir build make -C build/ clean all"
  }
  stage('Test and Coverage') {
    sh "make -C build/ coverage"
  }
  stage('SonarQube Analysis') {
    def scannerHome = tool 'SonarQube Scanner';
    withSonarQubeEnv('SonarQube Server') {
      sh "/tmp/sonar-scanner-4.7.0.2747-linux/bin/sonar-scanner -Dsonar.cfamily.build-wrapper-output=build -Dsonar.coverageReportPaths=build/coverage.xml"
    }
  }
}
