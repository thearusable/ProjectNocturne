import jenkins.model.*
jenkins = Jenkins.instance

pipeline {
  agent {
    node {
      label any
    }

  }
  stages {
    stage('checkout') {
      steps {
        git(url: 'https://github.com/thearusable/ProjectNocturne', branch: 'develop', changelog: true)
      }
    }
  }
}
